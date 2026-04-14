/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/dump/controller.hpp"

#include <fmt/chrono.h>

#include "roq/logging.hpp"

#include "roq/utils/debug/hex/message.hpp"

#include "roq/utils/pcap/reader.hpp"

#include "roq/starbase/sbe/parser_2.hpp"
#include "roq/starbase/sbe/utils.hpp"

using namespace std::literals;

namespace roq {
namespace starbase {
namespace dump {

// === HELPERS ===

namespace {
struct Bridge final : public utils::pcap::Reader::Handler, public sbe::Parser2::Handler {
  explicit Bridge(Settings const &settings) : settings_{settings} {}

 protected:
  bool operator()(
      std::chrono::nanoseconds timestamp,
      [[maybe_unused]] std::string_view const &source_address,
      [[maybe_unused]] uint16_t source_port,
      std::string_view const &destination_address,
      uint16_t destination_port,
      std::span<std::byte const> const &payload) override {
    if (settings_.print_payload) {
      utils::debug::hex::Message message{payload};
      fmt::print("payload={}\n"sv, message);
    }
    fmt::print("---\ntimestamp={}, address={}, port={}"sv, timestamp, destination_address, destination_port);
    TraceInfo trace_info;
    sbe::Parser2::dispatch(*this, payload, trace_info);
    fmt::print("\n"sv);
    return false;
  }

  bool operator()(sbe::PacketHeader const &packet_header) override {
    fmt::print(
        "\npacket_header={{sending_time={}, seq_num={}, channel_id={}, type={}, message_count={}}}"sv,
        packet_header.sending_time,
        packet_header.seq_num,
        packet_header.channel_id,
        packet_header.type,
        packet_header.message_count);
    index_ = 0;
    return true;
  }
  //
  void operator()(
      Trace<deribit::sbe::market_data::Instrument> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    print(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::TradingStatusUpdate> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    print(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::InstrumentInfo> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    print(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::InstrumentRef> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    print(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::BidPut> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    print(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::AskPut> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    print(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::BidQtyReduced> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    print(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::AskQtyReduced> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    print(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::BidDelete> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    print(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::AskDelete> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    print(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::TradeSummary> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    print(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::Trade> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    print(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::BlockTrade> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    print(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::SnapshotHeader> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    print(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::SnapshotTrailer> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    print(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::EndOfCycle> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    print(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::RetransmitRequest> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    print(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::RetransmitReject> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    print(event, message_header, packet_header);
  }

  void print(auto &event, auto &message_header, [[maybe_unused]] auto &packet_header) {
    using value_type = std::remove_cvref_t<decltype(event)>::value_type;
    auto &value = const_cast<value_type &>(event.value);  // note! not const-safe
    using header_type = std::remove_cvref_t<decltype(message_header)>;
    auto &header = const_cast<header_type &>(message_header);  // note! not const-safe
    fmt::print("\n[{}] message_header={}, {}={}"sv, index_++, header, get_name<value_type>(), value);
  }

 private:
  Settings const &settings_;
  size_t index_ = {};
};
}  // namespace

// === IMPLEMENTATION ===

Controller::Controller(Settings const &settings, std::string_view const &pcap_path) : settings_{settings}, pcap_path_{pcap_path} {
}

void Controller::dispatch() {
  Bridge bridge{settings_};
  utils::pcap::Reader::dispatch(bridge, pcap_path_);
}

}  // namespace dump
}  // namespace starbase
}  // namespace roq
