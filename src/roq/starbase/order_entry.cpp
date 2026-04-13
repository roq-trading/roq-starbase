/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/order_entry.hpp"

#include <algorithm>
#include <utility>

#include "roq/mask.hpp"

#include "roq/server/oms/exceptions.hpp"

#include "roq/utils/common.hpp"
#include "roq/utils/safe_cast.hpp"
#include "roq/utils/update.hpp"

#include "roq/utils/charconv/from_chars.hpp"
#include "roq/utils/charconv/to_string.hpp"

#include "roq/utils/metrics/factory.hpp"

#include "roq/utils/debug/fix/message.hpp"
#include "roq/utils/debug/hex/message.hpp"

#include "roq/fix/map.hpp"
#include "roq/fix/reader.hpp"

#include "roq/starbase/common.hpp"

using namespace std::literals;

namespace roq {
namespace starbase {

// === CONSTANTS ===

namespace {
auto const NAME = "om"sv;

auto const SUPPORTS = Mask{
    SupportType::CREATE_ORDER,
    SupportType::MODIFY_ORDER,
    SupportType::CANCEL_ORDER,
    SupportType::ORDER_ACK,
    SupportType::ORDER,
    SupportType::TRADE,
    SupportType::POSITION,
};

auto const LOGOUT_RESPONSE = "LOGOUT"sv;
}  // namespace

// === HELPERS ===

namespace {
auto create_name(auto stream_id, auto const &account) {
  return fmt::format("{}:{}:{}"sv, stream_id, NAME, account);
}

auto create_connection_factory(auto &settings, auto &context) {
  auto uri = settings.fix.uri;
  auto config = io::net::ConnectionFactory::Config{
      .interface = settings.misc.test_local_interface,
      .uris = {&uri, 1},
      .validate_certificate = settings.net.tls_validate_certificate,
  };
  return io::net::ConnectionFactory::create(context, config);
}

auto create_connection_manager(auto &handler, auto &settings, auto &connection_factory) {
  auto config = io::net::ConnectionManager::Config{
      .connection_timeout = settings.net.connection_timeout,
      .disconnect_on_idle_timeout = {},
      .always_reconnect = true,
  };
  return io::net::ConnectionManager::create(handler, connection_factory, config);
}

struct create_metrics final : public utils::metrics::Factory {
  create_metrics(auto &settings, auto &group, auto const &function) : utils::metrics::Factory{settings.app.name, group, function} {}
};
}  // namespace

// === IMPLEMENTATION ===

OrderEntry::OrderEntry(Handler &handler, io::Context &context, uint16_t stream_id, Account &account, Shared &shared)
    : handler_{handler}, stream_id_{stream_id}, name_{create_name(stream_id_, account.name)},
      connection_factory_{create_connection_factory(shared.settings, context)},
      connection_manager_{create_connection_manager(*this, shared.settings, *connection_factory_)}, decode_buffer_(shared.settings.misc.decode_buffer_size),
      encode_buffer_2_(shared.settings.misc.encode_buffer_size),
      counter_{
          .disconnect = create_metrics(shared.settings, name_, "disconnect"sv),
      },
      profile_{
          .parse = create_metrics(shared.settings, name_, "parse"sv),
          .position_report = create_metrics(shared.settings, name_, "position_report"sv),
          .execution_report = create_metrics(shared.settings, name_, "execution_report"sv),
          .order_cancel_reject = create_metrics(shared.settings, name_, "order_cancel_reject"sv),
          .reject = create_metrics(shared.settings, name_, "reject"sv),
          .order_mass_cancel_report = create_metrics(shared.settings, name_, "order_mass_cancel_report"sv),
      },
      latency_{
          .ping = create_metrics(shared.settings, name_, "ping"sv),
      },
      account_{account}, shared_{shared}, download_{shared.settings.fix.request_timeout, [this](auto state) { return download(state); }} {
}

void OrderEntry::operator()(Event<Start> const &) {
  (*connection_manager_).start();
}

void OrderEntry::operator()(Event<Stop> const &) {
  (*connection_manager_).stop();
}

void OrderEntry::operator()(Event<Timer> const &event) {
  if (!(*connection_manager_).refresh(event.value.now)) {
    return;
  }
  if (last_logon_or_heartbeat_.count() != 0 && shared_.settings.fix.request_timeout.count() != 0 &&
      (event.value.now - last_logon_or_heartbeat_) > shared_.settings.fix.request_timeout) {
    log::warn("*** DETECTED TIMEOUT ***"sv);
    log::info("DEBUG: now={}, last_logon_or_heartbeat={}"sv, event.value.now, last_logon_or_heartbeat_);
    log::info("closing connection"sv);
    (*connection_manager_).close();
  } else {
    if (ready_) {
      if (test_disconnect_time_.count() != 0 && test_disconnect_time_ < event.value.now) [[unlikely]] {
        if (shared_.settings.fix.test_order_disconnect.count() != 0) {
          log::warn("*** TEST: DISCONNECT ***"sv);
          log::info("closing connection"sv);
          (*connection_manager_).close();
        }
      } else {
        if (next_heartbeat_ <= event.value.now) {
          assert(shared_.settings.fix.ping_freq.count() > 0);
          next_heartbeat_ = event.value.now + shared_.settings.fix.ping_freq;
          send_test_request(clock::get_system());
        }
      }
    } else {
      if (test_logon_time_.count() != 0 && test_logon_time_ < event.value.now) {
        if (shared_.settings.fix.test_order_logon.count() != 0) {
          log::warn("*** TEST: LOGON ***"sv);
        }
        test_logon_time_ = {};
        send_logon();
        (*this)(ConnectionStatus::LOGIN_SENT);
      }
    }
  }
}

uint16_t OrderEntry::operator()(
    Event<CreateOrder> const &event, server::oms::Order const &, server::oms::RefData const &ref_data, std::string_view const &request_id) {
  if (!ready()) [[unlikely]] {
    throw server::oms::NotReady{"not ready"sv};
  }
  log::fatal("NOT IMPLEMENTED"sv);
  return stream_id_;
}

uint16_t OrderEntry::operator()(
    Event<ModifyOrder> const &event,
    server::oms::Order const &order,
    server::oms::RefData const &ref_data,
    std::string_view const &request_id,
    [[maybe_unused]] std::string_view const &previous_request_id) {
  if (!ready()) [[unlikely]] {
    throw server::oms::NotReady{"not ready"sv};
  }
  log::fatal("NOT IMPLEMENTED"sv);
  return stream_id_;
}

uint16_t OrderEntry::operator()(
    Event<CancelOrder> const &,
    server::oms::Order const &order,
    server::oms::RefData const &,
    std::string_view const &request_id,
    [[maybe_unused]] std::string_view const &previous_request_id) {
  if (!ready()) [[unlikely]] {
    throw server::oms::NotReady{"not ready"sv};
  }
  log::fatal("NOT IMPLEMENTED"sv);
  return stream_id_;
}

uint16_t OrderEntry::operator()(Event<CancelAllOrders> const &event, std::string_view const &request_id) {
  if (!ready()) [[unlikely]] {
    throw server::oms::NotReady{"not ready"sv};
  }
  log::fatal("NOT IMPLEMENTED"sv);
  return stream_id_;
}

void OrderEntry::operator()(metrics::Writer &writer) const {
  writer  //
      .write(counter_.disconnect, metrics::Type::COUNTER)
      .write(profile_.parse, metrics::Type::PROFILE)
      .write(profile_.execution_report, metrics::Type::PROFILE)
      .write(profile_.order_cancel_reject, metrics::Type::PROFILE)
      .write(profile_.reject, metrics::Type::PROFILE)
      .write(profile_.order_mass_cancel_report, metrics::Type::PROFILE)
      .write(latency_.ping, metrics::Type::LATENCY);
}

void OrderEntry::operator()(io::net::ConnectionManager::Connected const &) {
  assert(test_logon_time_.count() == 0);
  auto now = clock::get_system();
  test_logon_time_ = now + shared_.settings.fix.test_order_logon;
  if (shared_.settings.fix.test_order_disconnect.count() != 0) {
    test_disconnect_time_ = now + shared_.settings.fix.test_order_disconnect;
  }
}

void OrderEntry::operator()(io::net::ConnectionManager::Disconnected const &) {
  ++counter_.disconnect;
  outbound_ = {};
  inbound_ = {};
  ready_ = false;
  next_heartbeat_ = {};
  (*this)(ConnectionStatus::DISCONNECTED);
  download_.reset();
  last_logon_or_heartbeat_ = {};
  // test
  test_logon_time_ = {};
  test_disconnect_time_ = {};
}

void OrderEntry::operator()(io::net::ConnectionManager::Read const &) {
  auto buffer = (*connection_manager_).buffer();
  size_t total_bytes = 0;
  while (!std::empty(buffer)) {
    TraceInfo trace_info;
    if (sbe::Parser::dispatch(*this, buffer, trace_info)) {
      total_bytes += std::size(buffer);
    } else {
      log::fatal("Unexpected"sv);
    }
  }
  (*connection_manager_).drain(total_bytes);
}

void OrderEntry::operator()(io::net::ConnectionManager::Write const &) {
}

void OrderEntry::operator()(ConnectionStatus connection_status, std::string_view const &reason) {
  connection_status_ = connection_status;
  TraceInfo trace_info;
  auto stream_status = StreamStatus{
      .stream_id = stream_id_,
      .account = account_.name,
      .supports = SUPPORTS,
      .transport = Transport::TCP,
      .protocol = Protocol::FIX,
      .encoding = {Encoding::FIX},
      .priority = Priority::PRIMARY,
      .connection_status = connection_status_,
      .reason = reason,
      .interface = (*connection_factory_).get_interface(),
      .authority = (*connection_factory_).get_current_authority(),
      .path = (*connection_factory_).get_current_path(),
      .proxy = {},
  };
  log::info("stream_status={}"sv, stream_status);
  create_trace_and_dispatch(handler_, trace_info, stream_status);
}

void OrderEntry::send_logon() {
}

void OrderEntry::send_logout(std::string_view const &text) {
}

void OrderEntry::send_heartbeat(std::string_view const &test_req_id) {
}

void OrderEntry::send_test_request(std::chrono::nanoseconds now) {
}

uint32_t OrderEntry::download(OrderEntryState state) {
  switch (state) {
    using enum OrderEntryState;
    case UNDEFINED:
      assert(false);
      break;
    case POSITIONS:
      return 0;
    case ORDERS:
      return 0;
    case DONE:
      (*this)(ConnectionStatus::READY);
      assert(!ready_);
      ready_ = true;
      return 0;
  }
  assert(false);
  return 0;
}

// sbe::Parser::Handler

bool OrderEntry::operator()(sbe::Frame const &) {
  return true;
}

void OrderEntry::operator()(Trace<deribit_sbe_order::Logon> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::LogonConf> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::Logout> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::LoggedOut> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::Heartbeat> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::TestRequest> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::ResendRequest> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::GapFill> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::Reject> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::NewOrderRequest> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::AmendOrderRequest> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::CancelOrderRequest> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::MassQuoteRequest> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::MassCancelRequest> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::MassQuoteCancelRequest> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::NewOrderResponse> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::NewOrderReject> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::AmendOrderResponse> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::AmendOrderReject> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::CancelOrderResponse> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::CancelOrderReject> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::MassQuoteResponse> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::MassQuoteReject> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::MassCancelResponse> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::MassCancelReject> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::OrderFilled> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::OrdersCanceled> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::OrderPlaced> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::MassQuoteOrdersPlaced> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::MassQuoteMmpTriggered> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::OrdersMmpTriggered> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::MassQuoteMmpUnfrozen> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::OrdersMmpUnfrozen> const &, sbe::Frame const &) {
}

void OrderEntry::operator()(Trace<deribit_sbe_order::DummyMessage> const &, sbe::Frame const &) {
}

}  // namespace starbase
}  // namespace roq
