/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/dump/controller.hpp"

#include <fmt/chrono.h>

#include <starbase_sbe/MessageHeader.h>

#include "roq/logging.hpp"

#include "roq/utils/debug/hex/message.hpp"

#include "roq/utils/pcap/reader.hpp"

#include "roq/starbase/sbe/parser.hpp"
#include "roq/starbase/sbe/utils.hpp"

using namespace std::literals;

namespace roq {
namespace starbase {
namespace dump {

// === HELPERS ===

namespace {
struct Bridge final : public utils::pcap::Reader::Handler, public sbe::Parser::Handler {
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
    fmt::print("message={{timestamp={}, address={}, port={}"sv, timestamp, destination_address, destination_port);
    TraceInfo trace_info;
    sbe::Parser::dispatch(*this, payload, trace_info);
    fmt::print("}}\n"sv);
    return false;
  }

  bool operator()(sbe::Frame const &) override { return true; }

  void operator()(Trace<starbase_sbe::Instrument> const &event, sbe::Frame const &frame) override { print(event, frame); }
  void operator()(Trace<starbase_sbe::Book> const &event, sbe::Frame const &frame) override { print(event, frame); }
  void operator()(Trace<starbase_sbe::Trades> const &event, sbe::Frame const &frame) override { print(event, frame); }
  void operator()(Trace<starbase_sbe::Ticker> const &event, sbe::Frame const &frame) override { print(event, frame); }
  void operator()(Trace<starbase_sbe::Snapshot> const &event, sbe::Frame const &frame) override { print(event, frame); }
  void operator()(Trace<starbase_sbe::SnapshotStart> const &event, sbe::Frame const &frame) override { print(event, frame); }
  void operator()(Trace<starbase_sbe::SnapshotEnd> const &event, sbe::Frame const &frame) override { print(event, frame); }
  void operator()(Trace<starbase_sbe::ComboLegs> const &event, sbe::Frame const &frame) override { print(event, frame); }
  void operator()(Trace<starbase_sbe::PriceIndex> const &event, sbe::Frame const &frame) override { print(event, frame); }
  void operator()(Trace<starbase_sbe::Rfq> const &event, sbe::Frame const &frame) override { print(event, frame); }
  void operator()(Trace<starbase_sbe::InstrumentV2> const &event, sbe::Frame const &frame) override { print(event, frame); }

  void print(auto &event, auto &frame) {
    using value_type = std::remove_cvref_t<decltype(event)>::value_type;
    auto &value = const_cast<value_type &>(event.value);  // note! not const-safe
    fmt::print(", channel_id={}, sequence_number={}, {}={}"sv, frame.channel_id, frame.sequence_number, get_name<value_type>(), value);
  }

 private:
  Settings const &settings_;
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
