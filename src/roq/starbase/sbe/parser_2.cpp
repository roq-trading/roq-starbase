/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/sbe/parser_2.hpp"

#include "roq/logging.hpp"

#include "roq/utils/debug/hex/message.hpp"

#include "roq/starbase/sbe/frame.hpp"
#include "roq/starbase/sbe/utils.hpp"

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

bool Parser2::dispatch(Handler &handler, std::span<std::byte const> const &buffer, TraceInfo const &trace_info) {
  auto callback = [&](auto &frame, auto &packet) -> bool {
    // log::debug("frame={}"sv, frame);
    if (!handler(frame)) {
      return false;
    }
    while (!std::empty(packet)) {
      // log::debug("len(packet)={}"sv, std::size(packet));
      // log::debug("packet={}"sv, utils::debug::hex::Message{packet});
      auto length_message_header = deribit_sbe_market_data::MdMessageHeader::encodedLength();
      assert(std::size(packet) >= length_message_header);
      auto tmp = sbe_buffer(packet);
      deribit_sbe_market_data::MdMessageHeader message_header{std::data(tmp), std::size(tmp)};
      auto message = packet.subspan(length_message_header);
      auto template_id = message_header.templateId();
      // log::debug("template_id={}"sv, template_id);
      auto bytes = length_message_header;
      switch (template_id) {
        case deribit_sbe_market_data::Instrument::SBE_TEMPLATE_ID:  // 10
          bytes += dispatch_helper<deribit_sbe_market_data::Instrument>(handler, trace_info, message, frame);
          break;
        case deribit_sbe_market_data::TradingStatusUpdate::SBE_TEMPLATE_ID:  // 12
          bytes += dispatch_helper<deribit_sbe_market_data::TradingStatusUpdate>(handler, trace_info, message, frame);
          break;
        case deribit_sbe_market_data::InstrumentInfo::SBE_TEMPLATE_ID:  // 13
          bytes += dispatch_helper<deribit_sbe_market_data::InstrumentInfo>(handler, trace_info, message, frame);
          break;
        case deribit_sbe_market_data::InstrumentRef::SBE_TEMPLATE_ID:  // 14
          bytes += dispatch_helper<deribit_sbe_market_data::InstrumentRef>(handler, trace_info, message, frame);
          break;
        case deribit_sbe_market_data::BidPut::SBE_TEMPLATE_ID:  // 20
          bytes += dispatch_helper<deribit_sbe_market_data::BidPut>(handler, trace_info, message, frame);
          break;
        case deribit_sbe_market_data::AskPut::SBE_TEMPLATE_ID:  // 21
          bytes += dispatch_helper<deribit_sbe_market_data::AskPut>(handler, trace_info, message, frame);
          break;
        case deribit_sbe_market_data::BidQtyReduced::SBE_TEMPLATE_ID:  // 22
          bytes += dispatch_helper<deribit_sbe_market_data::BidQtyReduced>(handler, trace_info, message, frame);
          break;
        case deribit_sbe_market_data::AskQtyReduced::SBE_TEMPLATE_ID:  // 23
          bytes += dispatch_helper<deribit_sbe_market_data::AskQtyReduced>(handler, trace_info, message, frame);
          break;
        case deribit_sbe_market_data::BidDelete::SBE_TEMPLATE_ID:  // 24
          bytes += dispatch_helper<deribit_sbe_market_data::BidDelete>(handler, trace_info, message, frame);
          break;
        case deribit_sbe_market_data::AskDelete::SBE_TEMPLATE_ID:  // 25
          bytes += dispatch_helper<deribit_sbe_market_data::AskDelete>(handler, trace_info, message, frame);
          break;
        case deribit_sbe_market_data::TradeSummary::SBE_TEMPLATE_ID:  // 30
          bytes += dispatch_helper<deribit_sbe_market_data::TradeSummary>(handler, trace_info, message, frame);
          break;
        case deribit_sbe_market_data::Trade::SBE_TEMPLATE_ID:  // 31
          bytes += dispatch_helper<deribit_sbe_market_data::Trade>(handler, trace_info, message, frame);
          break;
        case deribit_sbe_market_data::BlockTrade::SBE_TEMPLATE_ID:  // 33
          bytes += dispatch_helper<deribit_sbe_market_data::BlockTrade>(handler, trace_info, message, frame);
          break;
        case deribit_sbe_market_data::SnapshotHeader::SBE_TEMPLATE_ID:  // 100
          bytes += dispatch_helper<deribit_sbe_market_data::SnapshotHeader>(handler, trace_info, message, frame);
          break;
        case deribit_sbe_market_data::SnapshotTrailer::SBE_TEMPLATE_ID:  // 101
          bytes += dispatch_helper<deribit_sbe_market_data::SnapshotTrailer>(handler, trace_info, message, frame);
          break;
        case deribit_sbe_market_data::EndOfCycle::SBE_TEMPLATE_ID:  // 119
          bytes += dispatch_helper<deribit_sbe_market_data::EndOfCycle>(handler, trace_info, message, frame);
          break;
        case deribit_sbe_market_data::RetransmitRequest::SBE_TEMPLATE_ID:  // 200
          bytes += dispatch_helper<deribit_sbe_market_data::RetransmitRequest>(handler, trace_info, message, frame);
          break;
        case deribit_sbe_market_data::RetransmitReject::SBE_TEMPLATE_ID:  // 202
          bytes += dispatch_helper<deribit_sbe_market_data::RetransmitReject>(handler, trace_info, message, frame);
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
