/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <string>

#include "roq/utils/container.hpp"

#include "roq/utils/metrics/counter.hpp"
#include "roq/utils/metrics/latency.hpp"
#include "roq/utils/metrics/profile.hpp"

#include "roq/io/context.hpp"

#include "roq/io/net/connection_factory.hpp"
#include "roq/io/net/connection_manager.hpp"

#include "roq/core/download.hpp"

#include "roq/server.hpp"

#include "roq/starbase/gateway/account.hpp"
#include "roq/starbase/gateway/shared.hpp"

#include "roq/starbase/protocol/sbe/parser.hpp"

namespace roq {
namespace starbase {
namespace gateway {

struct OrderEntry final : public io::net::ConnectionManager::Handler, protocol::sbe::Parser::Handler {
  struct Handler {};

  OrderEntry(Handler &, io::Context &, uint16_t stream_id, Account &, Shared &);

  OrderEntry(OrderEntry const &) = delete;

  void operator()(Event<Start> const &);
  void operator()(Event<Stop> const &);
  void operator()(Event<Timer> const &);

  uint16_t operator()(Event<CreateOrder> const &, server::oms::Order const &, server::oms::RefData const &, std::string_view const &request_id);
  uint16_t operator()(
      Event<ModifyOrder> const &,
      server::oms::Order const &,
      server::oms::RefData const &,
      std::string_view const &request_id,
      std::string_view const &previous_request_id);
  uint16_t operator()(
      Event<CancelOrder> const &,
      server::oms::Order const &,
      server::oms::RefData const &,
      std::string_view const &request_id,
      std::string_view const &previous_request_id);

  uint16_t operator()(Event<CancelAllOrders> const &, std::string_view const &request_id);

  void operator()(metrics::Writer &) const;

 protected:
  // protocol::sbe::Parser::Handler

  void operator()(Trace<deribit::sbe::order::Logon> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::LogonConf> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::Logout> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::LoggedOut> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::Heartbeat> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::TestRequest> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::ResendRequest> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::GapFill> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::Reject> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::NewOrderRequest> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::AmendOrderRequest> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::CancelOrderRequest> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::MassQuoteRequest> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::MassCancelRequest> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::MassQuoteCancelRequest> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::NewOrderResponse> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::NewOrderReject> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::AmendOrderResponse> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::AmendOrderReject> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::CancelOrderResponse> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::CancelOrderReject> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::MassQuoteResponse> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::MassQuoteReject> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::MassCancelResponse> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::MassCancelReject> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::OrderFilled> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::OrdersCanceled> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::OrderPlaced> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::MassQuoteOrdersPlaced> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::MassQuoteMmpTriggered> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::OrdersMmpTriggered> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::MassQuoteMmpUnfrozen> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::OrdersMmpUnfrozen> const &, deribit::sbe::order::MessageHeader const &) override;
  void operator()(Trace<deribit::sbe::order::DummyMessage> const &, deribit::sbe::order::MessageHeader const &) override;

  // io::net::ConnectionManager::Handler

  void operator()(io::net::ConnectionManager::Connected const &) override;
  void operator()(io::net::ConnectionManager::Disconnected const &) override;
  void operator()(io::net::ConnectionManager::Read const &) override;
  void operator()(io::net::ConnectionManager::Write const &) override;

  // helpers

  bool ready() const { return connection_status_ == ConnectionStatus::READY; }

  void operator()(ConnectionStatus, std::string_view const &reason = {});

  void send_logon();
  void send_logout(std::string_view const &text);
  void send_heartbeat(std::string_view const &test_req_id);
  void send_test_request(std::chrono::nanoseconds now);

  enum class State {
    UNDEFINED = 0,
    POSITIONS,
    ORDERS,
    DONE,
  };

  uint32_t download(State);

  template <typename T>
  uint64_t send(T const &event);

  template <typename T>
  uint64_t send(T const &event, std::chrono::nanoseconds sending_time);

 private:
  Handler &handler_;
  // config
  uint16_t const stream_id_;
  std::string const name_;
  // connection
  std::unique_ptr<io::net::ConnectionFactory> const connection_factory_;
  std::unique_ptr<io::net::ConnectionManager> const connection_manager_;
  // buffers
  std::vector<std::byte> decode_buffer_;
  std::vector<std::byte> encode_buffer_2_;
  std::string encode_buffer_;
  // metrics
  struct {
    utils::metrics::Counter disconnect;
  } counter_;
  struct {
    utils::metrics::Profile parse, position_report, execution_report, order_cancel_reject, reject, order_mass_cancel_report;
  } profile_;
  struct {
    utils::metrics::Latency ping;
  } latency_;
  // state
  struct {
    uint64_t msg_seq_num = {};
  } outbound_;
  struct {
    uint64_t msg_seq_num = {};
  } inbound_;
  // account
  Account &account_;
  // cache
  Shared &shared_;
  // state
  ConnectionStatus connection_status_ = {};

  // state
  bool ready_ = false;
  std::chrono::nanoseconds next_heartbeat_ = {};
  core::Download<State> download_;
  std::chrono::nanoseconds last_logon_or_heartbeat_ = {};
  // EXPERIMENTAL
  utils::unordered_map<uint64_t, RequestId> msg_seq_num_to_request_id_;
  std::chrono::nanoseconds test_disconnect_time_ = {};
  std::chrono::nanoseconds test_logon_time_ = {};
};

}  // namespace gateway
}  // namespace starbase
}  // namespace roq
