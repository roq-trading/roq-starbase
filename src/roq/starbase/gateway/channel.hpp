/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <vector>

#include "roq/mbp_update.hpp"

#include "roq/starbase/protocol/sbe/packet_header.hpp"

namespace roq {
namespace starbase {
namespace gateway {

struct Channel final {
  Channel() = default;

  Channel(Channel &&) = default;
  Channel(Channel const &) = delete;

  uint32_t previous_sequence_number() const { return previous_sequence_number_; }

  bool operator()(protocol::sbe::PacketHeader const &);

  void reset(protocol::sbe::PacketHeader const &);

  // snapshot

  void snapshot_start(protocol::sbe::PacketHeader const &);
  void snapshot_end(protocol::sbe::PacketHeader const &);

  bool ready() const { return ready_; }

 public:
  uint32_t instrument_id = {};
  std::vector<MBPUpdate> bids, asks;  // note! book/snapshot update may span multiple datagrams

 private:
  uint32_t previous_sequence_number_ = {};
  bool initialized_ = {};
  bool ready_ = {};
};

}  // namespace gateway
}  // namespace starbase
}  // namespace roq
