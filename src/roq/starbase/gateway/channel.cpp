/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/gateway/channel.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

namespace roq {
namespace starbase {
namespace gateway {

// === IMPLEMENTATION ===

bool Channel::operator()(sbe::PacketHeader const &packet_header) {
  auto result = true;
  if (packet_header.seq_num == (previous_sequence_number_ + 1)) [[likely]] {
    previous_sequence_number_ = packet_header.seq_num;
  } else {
    if (packet_header.seq_num == previous_sequence_number_) {
      log::debug("*** REPEAT ***"sv);
      result = false;
    } else {
      if (initialized_) {
        log::warn(
            "*** DETECTED PACKET DROP *** (channel_id={}, seq_num={}, previous_sequence_number={})"sv,
            packet_header.channel_id,
            packet_header.seq_num,
            previous_sequence_number_);
        result = false;
        ready_ = false;  // note!
      } else {
        assert(previous_sequence_number_ == 0);
        initialized_ = true;
      }
      previous_sequence_number_ = packet_header.seq_num;
    }
  }
  return result;
}

void Channel::reset(sbe::PacketHeader const &) {
  bids.clear();
  asks.clear();
  instrument_id = {};
  ready_ = {};
}

void Channel::snapshot_start(sbe::PacketHeader const &) {
  ready_ = true;
}

void Channel::snapshot_end(sbe::PacketHeader const &) {
  ready_ = false;
}

}  // namespace gateway
}  // namespace starbase
}  // namespace roq
