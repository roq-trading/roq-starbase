/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/sbe/frame.hpp"

#include "roq/logging.hpp"

#include "roq/utils/byte_order.hpp"

using namespace std::literals;

namespace roq {
namespace starbase {
namespace sbe {

// === HELPERS ===

namespace {
static_assert(sizeof(Frame) == Frame::size());
}

// === IMPLEMENTATION ===

// NOLINTBEGIN(readability-container-data-pointer)

Frame Frame::parse_helper(std::span<std::byte const> const &buffer) {
  if (std::size(buffer) < size()) {
    log::fatal("Invalid message, size={}"sv, std::size(buffer));
  }
  int64_t sending_time = {};
  std::memcpy(&sending_time, &buffer[0], sizeof(sending_time));
  sending_time = utils::little_endian_to_host(sending_time);
  int64_t seq_num;
  std::memcpy(&seq_num, &buffer[8], sizeof(seq_num));
  seq_num = utils::little_endian_to_host(seq_num);
  int32_t channel_id;
  std::memcpy(&channel_id, &buffer[16], sizeof(channel_id));
  channel_id = utils::little_endian_to_host(channel_id);
  uint16_t type;
  std::memcpy(&type, &buffer[20], sizeof(type));
  type = utils::little_endian_to_host(type);
  uint16_t message_count;
  std::memcpy(&message_count, &buffer[22], sizeof(message_count));
  message_count = utils::little_endian_to_host(message_count);
  return {
      .sending_time = std::chrono::nanoseconds{sending_time},
      .seq_num = seq_num,
      .channel_id = channel_id,
      .type = type,
      .message_count = message_count,
  };
}

// NOLINTEND(readability-container-data-pointer)

}  // namespace sbe
}  // namespace starbase
}  // namespace roq
