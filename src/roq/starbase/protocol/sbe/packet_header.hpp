/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <fmt/chrono.h>
#include <fmt/format.h>

#include <chrono>
#include <cstdint>
#include <span>

namespace roq {
namespace starbase {
namespace protocol {
namespace sbe {

// note! not auto-generated from XML
struct PacketHeader final {
  std::chrono::nanoseconds sending_time = {};
  int64_t seq_num = {};
  int32_t channel_id = {};
  uint16_t type = {};
  uint16_t message_count = {};

  static constexpr size_t size() { return 24; }

  template <typename Callback>
  static bool parse(std::span<std::byte const> const &buffer, Callback callback) {
    auto frame = parse_helper(buffer);
    auto packet = buffer.subspan(sizeof(PacketHeader));
    return callback(frame, packet);
  }

 private:
  static PacketHeader parse_helper(std::span<std::byte const> const &buffer);
};

}  // namespace sbe
}  // namespace protocol
}  // namespace starbase
}  // namespace roq

template <>
struct fmt::formatter<roq::starbase::protocol::sbe::PacketHeader> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(roq::starbase::protocol::sbe::PacketHeader const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(sending_time={}, )"
        R"(seq_num={}, )"
        R"(channel_id={}, )"
        R"(type={}, )"
        R"(message_count={})"
        R"(}})"sv,
        value.sending_time,
        value.seq_num,
        value.channel_id,
        value.type,
        value.message_count);
  }
};
