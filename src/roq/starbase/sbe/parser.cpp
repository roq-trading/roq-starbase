/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/sbe/parser.hpp"

#include "roq/logging.hpp"

#include "roq/utils/debug/hex/message.hpp"

#include "roq/starbase/sbe/frame.hpp"
// #include "roq/starbase/sbe/utils.hpp"

using namespace std::literals;

namespace roq {
namespace starbase {
namespace sbe {

// === HELPERS ===

namespace {
auto sbe_buffer(auto &buffer) {
  return std::span{const_cast<char *>(reinterpret_cast<char const *>(std::data(buffer))), std::size(buffer)};
}

template <typename T>
auto dispatch_helper(auto &handler, auto &trace_info, auto &message, auto &frame) {
  auto tmp = sbe_buffer(message);
  T value{std::data(tmp), std::size(tmp)};
  auto bytes = compute_length(value);
  value.sbeRewind();  // note!
  create_trace_and_dispatch(handler, trace_info, value, frame);
  return bytes;
}
}  // namespace

// === IMPLEMENTATION ===

bool Parser::dispatch(Handler &handler, std::span<std::byte const> const &buffer, TraceInfo const &trace_info) {
  auto callback = [&](auto &frame, auto &packet) -> bool {
    // log::debug("frame={}"sv, frame);
    if (!handler(frame)) {
      return false;
    }
    while (!std::empty(packet)) {
      // log::debug("len(packet)={}"sv, std::size(packet));
      // log::debug("packet={}"sv, utils::debug::hex::Message{packet});
      auto length_message_header = deribit_sbe_order::MessageHeader::encodedLength();
      assert(std::size(packet) >= length_message_header);
      auto tmp = sbe_buffer(packet);
      deribit_sbe_order::MessageHeader message_header{std::data(tmp), std::size(tmp)};
      auto message = packet.subspan(length_message_header);
      auto template_id = message_header.templateId();
      // log::debug("template_id={}"sv, template_id);
      auto bytes = length_message_header;
      switch (template_id) {
        // 1
        case deribit_sbe_order::Logon::SBE_TEMPLATE_ID:
          bytes += dispatch_helper<deribit_sbe_order::Instrument>(handler, trace_info, message, frame);
          break;
        // 1001
        case deribit_sbe_order::Book::SBE_TEMPLATE_ID:
          bytes += dispatch_helper<deribit_sbe_order::Book>(handler, trace_info, message, frame);
          break;
        // 1002
        case deribit_sbe_order::Trades::SBE_TEMPLATE_ID:
          bytes += dispatch_helper<deribit_sbe_order::Trades>(handler, trace_info, message, frame);
          break;
        // 1003
        case deribit_sbe_order::Ticker::SBE_TEMPLATE_ID:
          bytes += dispatch_helper<deribit_sbe_order::Ticker>(handler, trace_info, message, frame);
          break;
        // 1004
        case deribit_sbe_order::Snapshot::SBE_TEMPLATE_ID:
          bytes += dispatch_helper<deribit_sbe_order::Snapshot>(handler, trace_info, message, frame);
          break;
        // 1005
        case deribit_sbe_order::SnapshotStart::SBE_TEMPLATE_ID:
          bytes += dispatch_helper<deribit_sbe_order::SnapshotStart>(handler, trace_info, message, frame);
          break;
        // 1006
        case deribit_sbe_order::SnapshotEnd::SBE_TEMPLATE_ID:
          bytes += dispatch_helper<deribit_sbe_order::SnapshotEnd>(handler, trace_info, message, frame);
          break;
        // 1007
        case deribit_sbe_order::ComboLegs::SBE_TEMPLATE_ID:
          bytes += dispatch_helper<deribit_sbe_order::ComboLegs>(handler, trace_info, message, frame);
          break;
        // 1008
        case deribit_sbe_order::PriceIndex::SBE_TEMPLATE_ID:
          bytes += dispatch_helper<deribit_sbe_order::PriceIndex>(handler, trace_info, message, frame);
          break;
        // 1009
        case deribit_sbe_order::Rfq::SBE_TEMPLATE_ID:
          bytes += dispatch_helper<deribit_sbe_order::Rfq>(handler, trace_info, message, frame);
          break;
        // 1010
        case deribit_sbe_order::InstrumentV2::SBE_TEMPLATE_ID:
          bytes += dispatch_helper<deribit_sbe_order::InstrumentV2>(handler, trace_info, message, frame);
          break;
        default:
          log::warn("payload={}"sv, utils::debug::hex::Message{buffer});
          log::fatal("Unexpected: template_id={}"sv, template_id);
      }
      // log::debug("bytes={}"sv, bytes);
      assert(bytes <= std::size(packet));
      packet = packet.subspan(bytes);
    }
    if (!std::empty(packet)) {
      log::warn("payload={}"sv, utils::debug::hex::Message{buffer});
      log::fatal("Unexpected"sv);
    }
    return true;
  };
  return Frame::parse(buffer, callback);
}

}  // namespace sbe
}  // namespace starbase
}  // namespace roq
