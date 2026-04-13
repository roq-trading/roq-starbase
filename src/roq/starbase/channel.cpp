/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/channel.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

namespace roq {
namespace starbase {

// === IMPLEMENTATION ===

bool Channel::operator()(sbe::Frame const &frame) {
  auto result = true;
  if (frame.seq_num == (previous_sequence_number_ + 1)) [[likely]] {
    previous_sequence_number_ = frame.seq_num;
  } else {
    if (frame.seq_num == previous_sequence_number_) {
      log::debug("*** REPEAT ***"sv);
      result = false;
    } else {
      if (initialized_) {
        log::warn(
            "*** DETECTED PACKET DROP *** (channel_id={}, seq_num={}, previous_sequence_number={})"sv,
            frame.channel_id,
            frame.seq_num,
            previous_sequence_number_);
        result = false;
        ready_ = false;  // note!
      } else {
        assert(previous_sequence_number_ == 0);
        initialized_ = true;
      }
      previous_sequence_number_ = frame.seq_num;
    }
  }
  return result;
}

void Channel::reset(sbe::Frame const &) {
  bids.clear();
  asks.clear();
  instrument_id = {};
  ready_ = {};
}

void Channel::snapshot_start(sbe::Frame const &) {
  ready_ = true;
}

void Channel::snapshot_end(sbe::Frame const &) {
  ready_ = false;
}

}  // namespace starbase
}  // namespace roq
