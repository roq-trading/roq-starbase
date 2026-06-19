/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/gateway/market_data_snapshot.hpp"

#include "roq/logging.hpp"

#include "roq/utils/update.hpp"

#include "roq/utils/debug/hex/message.hpp"

#include "roq/utils/metrics/factory.hpp"

#include "roq/io/network_address.hpp"

#include "roq/starbase/gateway/utils.hpp"

#include "roq/starbase/protocol/sbe/map.hpp"
#include "roq/starbase/protocol/sbe/utils.hpp"

using namespace std::literals;

namespace roq {
namespace starbase {
namespace gateway {

// === CONSTANTS ===

namespace {
auto const NAME = "udps"sv;
}

// === HELPERS ===

namespace {
auto create_name(auto stream_id) {
  return fmt::format("{}:{}"sv, stream_id, NAME);
}

auto publish_market_by_price(auto &settings) {
  return !settings.multicast.disable_market_by_price;
}

auto get_supports(auto publish_market_by_price) {
  Mask<SupportType> result;
  if (publish_market_by_price) {
    result |= SupportType::MARKET_BY_PRICE;
  }
  return result;
}

auto create_receiver(auto &handler, auto &settings, auto &context, auto &shared) {
  auto port = uint16_t{12345};  // auto port = shared.sbe_config.snapshot_port();
  log::info("Create multicast socket port={}"sv, port);
  auto network_address = io::NetworkAddress{port};
  auto socket_options = Mask{
      io::SocketOption::REUSE_ADDRESS,
  };
  auto receiver = context.create_udp_receiver(handler, network_address, socket_options);
  log::info(R"(Local interface is "{}")"sv, settings.multicast.local_interface);
  auto local_interface = io::NetworkAddress::create_blocking(settings.multicast.local_interface);
  auto callback = [&](auto &connection) {
    log::info(R"(Add membership "{}")"sv, connection.address);
    auto multicast_address_2 = io::NetworkAddress::create_blocking(connection.address);
    (*receiver).add_membership(multicast_address_2, local_interface);
  };
  // shared.sbe_config.get_connections(callback);
  return receiver;
}

struct create_metrics final : public utils::metrics::Factory {
  create_metrics(auto &settings, auto &group, auto const &function) : utils::metrics::Factory{settings.app.name, group, function} {}
};
}  // namespace

// === IMPLEMENTATION ===

MarketDataSnapshot::MarketDataSnapshot(Handler &handler, io::Context &context, uint16_t stream_id, Shared &shared)
    : handler_{handler}, stream_id_{stream_id}, name_{create_name(stream_id_)}, publish_market_by_price_{publish_market_by_price(shared.settings)},
      supports_{get_supports(publish_market_by_price_)}, receiver_{create_receiver(*this, shared.settings, context, shared)},
      counter_{
          .disconnect = create_metrics(shared.settings, name_, "disconnect"sv),
      },
      profile_{
          .parse = create_metrics(shared.settings, name_, "parse"sv),
      },
      shared_{shared} {
  log::info("publish_market_by_price={}"sv, publish_market_by_price_);
}

void MarketDataSnapshot::operator()(Event<Start> const &) {
  TraceInfo trace_info;
  last_update_time_ = trace_info.source_receive_time;
  publish_stream_status(trace_info, ConnectionStatus::CONNECTING);
}

void MarketDataSnapshot::operator()(Event<Stop> const &) {
}

void MarketDataSnapshot::operator()(Event<Timer> const &event) {
  if (last_update_time_.count() != 0 && (last_update_time_ + shared_.settings.multicast.timeout) < event.value.now) {
    log::warn("*** DETECTED TIMEOUT ***"sv);
    last_update_time_ = {};
  }
}

void MarketDataSnapshot::operator()(io::net::udp::Receiver::Read const &) {
  TraceInfo trace_info;
  last_update_time_ = trace_info.source_receive_time;
  publish_stream_status(trace_info, ConnectionStatus::READY);  // first message will publish
  while (true) {
    auto bytes = (*receiver_).recv(shared_.buffer);
    if (bytes == 0) {
      return;
    }
    log::info<5>("Received {} byte(s)"sv, bytes);
    std::span payload{std::data(shared_.buffer), bytes};
    log::info<5>("{}"sv, utils::debug::hex::Message{payload});
    if (!protocol::sbe::Parser2::dispatch(*this, payload, trace_info)) {
      // note! here is an option to use the re-order buffer -- but it's not A+B, so why bother?
    }
  }
}

void MarketDataSnapshot::operator()(io::net::udp::Receiver::Error const &error) {
  log::fatal("Error: what={}"sv, error.what);
}

bool MarketDataSnapshot::operator()(protocol::sbe::PacketHeader const &packet_header) {
  auto result = false;
  auto callback = [&](auto &channel) {
    result = channel(packet_header);
    if (!result) {
      channel.reset(packet_header);
    }
  };
  get_channel(packet_header, callback);
  return result;
}

void MarketDataSnapshot::operator()(
    Trace<deribit::sbe::market_data::Instrument> const &, deribit::sbe::market_data::MdMessageHeader const &, protocol::sbe::PacketHeader const &) {
}

void MarketDataSnapshot::operator()(
    Trace<deribit::sbe::market_data::TradingStatusUpdate> const &, deribit::sbe::market_data::MdMessageHeader const &, protocol::sbe::PacketHeader const &) {
}

void MarketDataSnapshot::operator()(
    Trace<deribit::sbe::market_data::InstrumentInfo> const &, deribit::sbe::market_data::MdMessageHeader const &, protocol::sbe::PacketHeader const &) {
}

void MarketDataSnapshot::operator()(
    Trace<deribit::sbe::market_data::InstrumentRef> const &, deribit::sbe::market_data::MdMessageHeader const &, protocol::sbe::PacketHeader const &) {
}

void MarketDataSnapshot::operator()(
    Trace<deribit::sbe::market_data::BidPut> const &, deribit::sbe::market_data::MdMessageHeader const &, protocol::sbe::PacketHeader const &) {
}

void MarketDataSnapshot::operator()(
    Trace<deribit::sbe::market_data::AskPut> const &, deribit::sbe::market_data::MdMessageHeader const &, protocol::sbe::PacketHeader const &) {
}

void MarketDataSnapshot::operator()(
    Trace<deribit::sbe::market_data::BidQtyReduced> const &, deribit::sbe::market_data::MdMessageHeader const &, protocol::sbe::PacketHeader const &) {
}

void MarketDataSnapshot::operator()(
    Trace<deribit::sbe::market_data::AskQtyReduced> const &, deribit::sbe::market_data::MdMessageHeader const &, protocol::sbe::PacketHeader const &) {
}

void MarketDataSnapshot::operator()(
    Trace<deribit::sbe::market_data::BidDelete> const &, deribit::sbe::market_data::MdMessageHeader const &, protocol::sbe::PacketHeader const &) {
}

void MarketDataSnapshot::operator()(
    Trace<deribit::sbe::market_data::AskDelete> const &, deribit::sbe::market_data::MdMessageHeader const &, protocol::sbe::PacketHeader const &) {
}

void MarketDataSnapshot::operator()(
    Trace<deribit::sbe::market_data::TradeSummary> const &, deribit::sbe::market_data::MdMessageHeader const &, protocol::sbe::PacketHeader const &) {
}

void MarketDataSnapshot::operator()(
    Trace<deribit::sbe::market_data::Trade> const &, deribit::sbe::market_data::MdMessageHeader const &, protocol::sbe::PacketHeader const &) {
}

void MarketDataSnapshot::operator()(
    Trace<deribit::sbe::market_data::BlockTrade> const &, deribit::sbe::market_data::MdMessageHeader const &, protocol::sbe::PacketHeader const &) {
}

void MarketDataSnapshot::operator()(
    Trace<deribit::sbe::market_data::SnapshotHeader> const &, deribit::sbe::market_data::MdMessageHeader const &, protocol::sbe::PacketHeader const &) {
}

void MarketDataSnapshot::operator()(
    Trace<deribit::sbe::market_data::SnapshotTrailer> const &, deribit::sbe::market_data::MdMessageHeader const &, protocol::sbe::PacketHeader const &) {
}

void MarketDataSnapshot::operator()(
    Trace<deribit::sbe::market_data::EndOfCycle> const &, deribit::sbe::market_data::MdMessageHeader const &, protocol::sbe::PacketHeader const &) {
}

void MarketDataSnapshot::operator()(
    Trace<deribit::sbe::market_data::RetransmitRequest> const &, deribit::sbe::market_data::MdMessageHeader const &, protocol::sbe::PacketHeader const &) {
}

void MarketDataSnapshot::operator()(
    Trace<deribit::sbe::market_data::RetransmitReject> const &, deribit::sbe::market_data::MdMessageHeader const &, protocol::sbe::PacketHeader const &) {
}

void MarketDataSnapshot::operator()(metrics::Writer &writer) const {
  writer  //
      .write(counter_.disconnect, metrics::Type::COUNTER)
      .write(profile_.parse, metrics::Type::PROFILE);
}

void MarketDataSnapshot::publish_stream_status(TraceInfo const &trace_info, ConnectionStatus connection_status, std::string_view const &reason) {
  connection_status_ = connection_status;
  auto stream_status = StreamStatus{
      .stream_id = stream_id_,
      .account = {},
      .supports = supports_,
      .transport = Transport::UDP,
      .protocol = Protocol::SBE,
      .encoding = {Encoding::SBE},
      .priority = Priority::PRIMARY,
      .connection_status = connection_status_,
      .reason = reason,
      .interface = {},
      .authority = {},
      .path = {},
      .proxy = {},
  };
  log::info("stream_status={}"sv, stream_status);
  create_trace_and_dispatch(shared_.dispatcher, trace_info, stream_status);
}

template <typename Callback>
void MarketDataSnapshot::get_channel(protocol::sbe::PacketHeader const &packet_header, Callback callback) {
  auto iter = channel_.find(packet_header.channel_id);
  if (iter == std::end(channel_)) {
    iter = channel_.try_emplace(packet_header.channel_id).first;
  }
  callback((*iter).second);
}

}  // namespace gateway
}  // namespace starbase
}  // namespace roq
