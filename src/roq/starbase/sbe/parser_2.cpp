/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/sbe/parser_2.hpp"

#include "roq/logging.hpp"

#include "roq/utils/debug/hex/message.hpp"

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
auto dispatch_helper(auto &handler, auto &trace_info, auto &message, auto &message_header, auto &packet_header) {
  auto tmp = sbe_buffer(message);
  T value{std::data(tmp), std::size(tmp)};
  auto bytes = compute_length(value);
  value.sbeRewind();  // note!
  create_trace_and_dispatch(handler, trace_info, value, message_header, packet_header);
  return bytes;
}
}  // namespace

// === IMPLEMENTATION ===

bool Parser2::dispatch(Handler &handler, std::span<std::byte const> const &buffer, TraceInfo const &trace_info) {
  auto callback = [&](auto &packet_header, auto &packet) -> bool {
    // log::warn("DEBUG packet_header={}"sv, packet_header);
    if (!handler(packet_header)) {
      return false;
    }
    while (!std::empty(packet)) {
      // log::warn("DEBUG len(packet)={}"sv, std::size(packet));
      // log::warn("DEBUG packet={}"sv, utils::debug::hex::Message{packet});
      auto length_message_header = deribit::sbe::market_data::MdMessageHeader::encodedLength();
      assert(std::size(packet) >= length_message_header);
      auto tmp = sbe_buffer(packet);
      deribit::sbe::market_data::MdMessageHeader message_header{std::data(tmp), std::size(tmp)};
      auto message = packet.subspan(length_message_header);
      auto template_id = message_header.templateId();
      // log::warn("DEBUG template_id={}"sv, template_id);
      auto bytes = length_message_header;
      // log::warn("DEBUG bytes={}"sv, bytes);
      switch (template_id) {
        case deribit::sbe::market_data::Instrument::SBE_TEMPLATE_ID:  // 10
          bytes += dispatch_helper<deribit::sbe::market_data::Instrument>(handler, trace_info, message, message_header, packet_header);
          break;
        case deribit::sbe::market_data::TradingStatusUpdate::SBE_TEMPLATE_ID:  // 12
          bytes += dispatch_helper<deribit::sbe::market_data::TradingStatusUpdate>(handler, trace_info, message, message_header, packet_header);
          break;
        case deribit::sbe::market_data::InstrumentInfo::SBE_TEMPLATE_ID:  // 13
          bytes += dispatch_helper<deribit::sbe::market_data::InstrumentInfo>(handler, trace_info, message, message_header, packet_header);
          break;
        case deribit::sbe::market_data::InstrumentRef::SBE_TEMPLATE_ID:  // 14
          bytes += dispatch_helper<deribit::sbe::market_data::InstrumentRef>(handler, trace_info, message, message_header, packet_header);
          break;
        case deribit::sbe::market_data::BidPut::SBE_TEMPLATE_ID:  // 20
          bytes += dispatch_helper<deribit::sbe::market_data::BidPut>(handler, trace_info, message, message_header, packet_header);
          break;
        case deribit::sbe::market_data::AskPut::SBE_TEMPLATE_ID:  // 21
          bytes += dispatch_helper<deribit::sbe::market_data::AskPut>(handler, trace_info, message, message_header, packet_header);
          break;
        case deribit::sbe::market_data::BidQtyReduced::SBE_TEMPLATE_ID:  // 22
          bytes += dispatch_helper<deribit::sbe::market_data::BidQtyReduced>(handler, trace_info, message, message_header, packet_header);
          break;
        case deribit::sbe::market_data::AskQtyReduced::SBE_TEMPLATE_ID:  // 23
          bytes += dispatch_helper<deribit::sbe::market_data::AskQtyReduced>(handler, trace_info, message, message_header, packet_header);
          break;
        case deribit::sbe::market_data::BidDelete::SBE_TEMPLATE_ID:  // 24
          bytes += dispatch_helper<deribit::sbe::market_data::BidDelete>(handler, trace_info, message, message_header, packet_header);
          break;
        case deribit::sbe::market_data::AskDelete::SBE_TEMPLATE_ID:  // 25
          bytes += dispatch_helper<deribit::sbe::market_data::AskDelete>(handler, trace_info, message, message_header, packet_header);
          break;
        case deribit::sbe::market_data::TradeSummary::SBE_TEMPLATE_ID:  // 30
          bytes += dispatch_helper<deribit::sbe::market_data::TradeSummary>(handler, trace_info, message, message_header, packet_header);
          break;
        case deribit::sbe::market_data::Trade::SBE_TEMPLATE_ID:  // 31
          bytes += dispatch_helper<deribit::sbe::market_data::Trade>(handler, trace_info, message, message_header, packet_header);
          break;
        case deribit::sbe::market_data::BlockTrade::SBE_TEMPLATE_ID:  // 33
          bytes += dispatch_helper<deribit::sbe::market_data::BlockTrade>(handler, trace_info, message, message_header, packet_header);
          break;
        case deribit::sbe::market_data::SnapshotHeader::SBE_TEMPLATE_ID:  // 100
          bytes += dispatch_helper<deribit::sbe::market_data::SnapshotHeader>(handler, trace_info, message, message_header, packet_header);
          break;
        case deribit::sbe::market_data::SnapshotTrailer::SBE_TEMPLATE_ID:  // 101
          bytes += dispatch_helper<deribit::sbe::market_data::SnapshotTrailer>(handler, trace_info, message, message_header, packet_header);
          break;
        case deribit::sbe::market_data::EndOfCycle::SBE_TEMPLATE_ID:  // 119
          bytes += dispatch_helper<deribit::sbe::market_data::EndOfCycle>(handler, trace_info, message, message_header, packet_header);
          break;
        case deribit::sbe::market_data::RetransmitRequest::SBE_TEMPLATE_ID:  // 200
          bytes += dispatch_helper<deribit::sbe::market_data::RetransmitRequest>(handler, trace_info, message, message_header, packet_header);
          break;
        case deribit::sbe::market_data::RetransmitReject::SBE_TEMPLATE_ID:  // 202
          bytes += dispatch_helper<deribit::sbe::market_data::RetransmitReject>(handler, trace_info, message, message_header, packet_header);
          break;
        default:
          log::warn("payload={}"sv, utils::debug::hex::Message{buffer});
          log::fatal("Unexpected: template_id={}"sv, template_id);
      }
      // log::warn("DEBUG bytes={}"sv, bytes);
      auto message_length = message_header.messageLength();
      if (message_length < bytes) {
        log::warn("DEBUG message_length={}, bytes={}"sv, message_length, bytes);  // XXX FIXME TODO due to alignment or something like that ???
      }
      // assert(bytes <= std::size(packet));
      // packet = packet.subspan(bytes);
      packet = packet.subspan(message_length);
    }
    if (!std::empty(packet)) {
      log::warn("payload={}"sv, utils::debug::hex::Message{buffer});
      log::fatal("Unexpected"sv);
    }
    return true;
  };
  return PacketHeader::parse(buffer, callback);
}

}  // namespace sbe
}  // namespace starbase
}  // namespace roq
