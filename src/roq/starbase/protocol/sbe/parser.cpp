/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/protocol/sbe/parser.hpp"

#include "roq/logging.hpp"

#include "roq/utils/debug/hex/message.hpp"

#include "roq/starbase/protocol/sbe/utils.hpp"

using namespace std::literals;

namespace roq {
namespace starbase {
namespace protocol {
namespace sbe {

// === HELPERS ===

namespace {
auto sbe_buffer(auto &buffer) {
  return std::span{const_cast<char *>(reinterpret_cast<char const *>(std::data(buffer))), std::size(buffer)};
}

template <typename T>
auto dispatch_helper(auto &handler, auto &trace_info, auto &message, auto &message_header) {
  // log::warn("len(message)={}"sv, std::size(message));
  // log::warn("message={}"sv, utils::debug::hex::Message{message});
  auto tmp = sbe_buffer(message);
  T value{std::data(tmp), std::size(tmp)};
  auto bytes = compute_length(value);
  value.sbeRewind();  // note!
  create_trace_and_dispatch(handler, trace_info, value, message_header);
  return bytes;
}
}  // namespace

// === IMPLEMENTATION ===

bool Parser::dispatch(Handler &handler, std::span<std::byte const> const &buffer, TraceInfo const &trace_info) {
  // log::warn("len(buffer)={}"sv, std::size(buffer));
  // log::warn("buffer={}"sv, utils::debug::hex::Message{buffer});
  auto length_message_header = deribit::sbe::order::MessageHeader::encodedLength();
  assert(std::size(buffer) >= length_message_header);
  auto tmp = sbe_buffer(buffer);
  deribit::sbe::order::MessageHeader message_header{std::data(tmp), std::size(tmp)};
  // log::warn("message_header={}"sv, message_header);
  auto message = buffer.subspan(length_message_header);
  auto message_type_id = message_header.messageTypeId();
  // log::warn("message_type_id={}"sv, message_type_id);
  auto bytes = length_message_header;
  switch (message_type_id) {
    case deribit::sbe::order::Logon::SBE_TEMPLATE_ID:  // 1
      bytes += dispatch_helper<deribit::sbe::order::Logon>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::LogonConf::SBE_TEMPLATE_ID:  // 2
      bytes += dispatch_helper<deribit::sbe::order::LogonConf>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::Logout::SBE_TEMPLATE_ID:  // 4
      bytes += dispatch_helper<deribit::sbe::order::Logout>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::LoggedOut::SBE_TEMPLATE_ID:  // 5
      bytes += dispatch_helper<deribit::sbe::order::LoggedOut>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::Heartbeat::SBE_TEMPLATE_ID:  // 10
      bytes += dispatch_helper<deribit::sbe::order::Heartbeat>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::TestRequest::SBE_TEMPLATE_ID:  // 11
      bytes += dispatch_helper<deribit::sbe::order::TestRequest>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::ResendRequest::SBE_TEMPLATE_ID:  // 20
      bytes += dispatch_helper<deribit::sbe::order::ResendRequest>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::GapFill::SBE_TEMPLATE_ID:  // 21
      bytes += dispatch_helper<deribit::sbe::order::GapFill>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::Reject::SBE_TEMPLATE_ID:  // 30
      bytes += dispatch_helper<deribit::sbe::order::Reject>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::NewOrderRequest::SBE_TEMPLATE_ID:  // 100
      bytes += dispatch_helper<deribit::sbe::order::NewOrderRequest>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::AmendOrderRequest::SBE_TEMPLATE_ID:  // 110
      bytes += dispatch_helper<deribit::sbe::order::AmendOrderRequest>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::CancelOrderRequest::SBE_TEMPLATE_ID:  // 120
      bytes += dispatch_helper<deribit::sbe::order::CancelOrderRequest>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::MassQuoteRequest::SBE_TEMPLATE_ID:  // 130
      bytes += dispatch_helper<deribit::sbe::order::MassQuoteRequest>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::MassCancelRequest::SBE_TEMPLATE_ID:  // 140
      bytes += dispatch_helper<deribit::sbe::order::MassCancelRequest>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::MassQuoteCancelRequest::SBE_TEMPLATE_ID:  // 145
      bytes += dispatch_helper<deribit::sbe::order::MassQuoteCancelRequest>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::NewOrderResponse::SBE_TEMPLATE_ID:  // 200
      bytes += dispatch_helper<deribit::sbe::order::NewOrderResponse>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::NewOrderReject::SBE_TEMPLATE_ID:  // 202
      bytes += dispatch_helper<deribit::sbe::order::NewOrderReject>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::AmendOrderResponse::SBE_TEMPLATE_ID:  // 210
      bytes += dispatch_helper<deribit::sbe::order::AmendOrderResponse>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::AmendOrderReject::SBE_TEMPLATE_ID:  // 212
      bytes += dispatch_helper<deribit::sbe::order::AmendOrderReject>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::CancelOrderResponse::SBE_TEMPLATE_ID:  // 220
      bytes += dispatch_helper<deribit::sbe::order::CancelOrderResponse>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::CancelOrderReject::SBE_TEMPLATE_ID:  // 222
      bytes += dispatch_helper<deribit::sbe::order::CancelOrderReject>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::MassQuoteResponse::SBE_TEMPLATE_ID:  // 230
      bytes += dispatch_helper<deribit::sbe::order::MassQuoteResponse>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::MassQuoteReject::SBE_TEMPLATE_ID:  // 232
      bytes += dispatch_helper<deribit::sbe::order::MassQuoteReject>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::MassCancelResponse::SBE_TEMPLATE_ID:  // 240
      bytes += dispatch_helper<deribit::sbe::order::MassCancelResponse>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::MassCancelReject::SBE_TEMPLATE_ID:  // 242
      bytes += dispatch_helper<deribit::sbe::order::MassCancelReject>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::OrderFilled::SBE_TEMPLATE_ID:  // 300
      bytes += dispatch_helper<deribit::sbe::order::OrderFilled>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::OrdersCanceled::SBE_TEMPLATE_ID:  // 310
      bytes += dispatch_helper<deribit::sbe::order::OrdersCanceled>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::OrderPlaced::SBE_TEMPLATE_ID:  // 312
      bytes += dispatch_helper<deribit::sbe::order::OrderPlaced>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::MassQuoteOrdersPlaced::SBE_TEMPLATE_ID:  // 314
      bytes += dispatch_helper<deribit::sbe::order::MassQuoteOrdersPlaced>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::MassQuoteMmpTriggered::SBE_TEMPLATE_ID:  // 320
      bytes += dispatch_helper<deribit::sbe::order::MassQuoteMmpTriggered>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::OrdersMmpTriggered::SBE_TEMPLATE_ID:  // 322
      bytes += dispatch_helper<deribit::sbe::order::OrdersMmpTriggered>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::MassQuoteMmpUnfrozen::SBE_TEMPLATE_ID:  // 324
      bytes += dispatch_helper<deribit::sbe::order::MassQuoteMmpUnfrozen>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::OrdersMmpUnfrozen::SBE_TEMPLATE_ID:  // 326
      bytes += dispatch_helper<deribit::sbe::order::OrdersMmpUnfrozen>(handler, trace_info, message, message_header);
      break;
    case deribit::sbe::order::DummyMessage::SBE_TEMPLATE_ID:  // 9999
      bytes += dispatch_helper<deribit::sbe::order::DummyMessage>(handler, trace_info, message, message_header);
      break;
    default:
      log::warn("payload={}"sv, utils::debug::hex::Message{buffer});
      log::fatal("Unexpected: message_type_id={}"sv, message_type_id);
  }
  return true;
}

}  // namespace sbe
}  // namespace protocol
}  // namespace starbase
}  // namespace roq
