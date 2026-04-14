/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <fmt/chrono.h>
#include <fmt/format.h>

#include <magic_enum/magic_enum_format.hpp>

// session
#include <deribit_sbe_order/GapFill.h>
#include <deribit_sbe_order/Heartbeat.h>
#include <deribit_sbe_order/LoggedOut.h>
#include <deribit_sbe_order/Logon.h>
#include <deribit_sbe_order/LogonConf.h>
#include <deribit_sbe_order/Logout.h>
#include <deribit_sbe_order/Reject.h>
#include <deribit_sbe_order/ResendRequest.h>
#include <deribit_sbe_order/TestRequest.h>

// application
#include <deribit_sbe_order/AmendOrderReject.h>
#include <deribit_sbe_order/AmendOrderRequest.h>
#include <deribit_sbe_order/AmendOrderResponse.h>
#include <deribit_sbe_order/CancelOrderReject.h>
#include <deribit_sbe_order/CancelOrderRequest.h>
#include <deribit_sbe_order/CancelOrderResponse.h>
#include <deribit_sbe_order/DummyMessage.h>
#include <deribit_sbe_order/MassCancelReject.h>
#include <deribit_sbe_order/MassCancelRequest.h>
#include <deribit_sbe_order/MassCancelResponse.h>
#include <deribit_sbe_order/MassQuoteCancelRequest.h>
#include <deribit_sbe_order/MassQuoteMmpTriggered.h>
#include <deribit_sbe_order/MassQuoteMmpUnfrozen.h>
#include <deribit_sbe_order/MassQuoteOrdersPlaced.h>
#include <deribit_sbe_order/MassQuoteReject.h>
#include <deribit_sbe_order/MassQuoteRequest.h>
#include <deribit_sbe_order/MassQuoteResponse.h>
#include <deribit_sbe_order/NewOrderReject.h>
#include <deribit_sbe_order/NewOrderRequest.h>
#include <deribit_sbe_order/NewOrderResponse.h>
#include <deribit_sbe_order/OrderFilled.h>
#include <deribit_sbe_order/OrderPlaced.h>
#include <deribit_sbe_order/OrdersCanceled.h>
#include <deribit_sbe_order/OrdersMmpTriggered.h>
#include <deribit_sbe_order/OrdersMmpUnfrozen.h>

// incremental
#include <deribit_sbe_market_data/AskDelete.h>
#include <deribit_sbe_market_data/AskPut.h>
#include <deribit_sbe_market_data/AskQtyReduced.h>
#include <deribit_sbe_market_data/BidDelete.h>
#include <deribit_sbe_market_data/BidPut.h>
#include <deribit_sbe_market_data/BidQtyReduced.h>
#include <deribit_sbe_market_data/BlockTrade.h>
#include <deribit_sbe_market_data/Instrument.h>
#include <deribit_sbe_market_data/InstrumentInfo.h>
#include <deribit_sbe_market_data/InstrumentRef.h>
#include <deribit_sbe_market_data/Trade.h>
#include <deribit_sbe_market_data/TradeSummary.h>
#include <deribit_sbe_market_data/TradingStatusUpdate.h>

// snapshot
#include <deribit_sbe_market_data/EndOfCycle.h>
#include <deribit_sbe_market_data/SnapshotHeader.h>
#include <deribit_sbe_market_data/SnapshotTrailer.h>

// retransmit
#include <deribit_sbe_market_data/RetransmitReject.h>
#include <deribit_sbe_market_data/RetransmitRequest.h>

#include "roq/api.hpp"
#include "roq/name.hpp"

#include "roq/core/sbe/iterator.hpp"

#include "roq/starbase/sbe/map.hpp"

namespace roq {
namespace starbase {
namespace sbe {

template <typename T>
size_t compute_length(T &);

// session

template <>
inline size_t compute_length(deribit_sbe_order::Logon &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::LogonConf &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::Logout &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::LoggedOut &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::Heartbeat &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::TestRequest &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::ResendRequest &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::GapFill &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::Reject &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

// application

template <>
inline size_t compute_length(deribit_sbe_order::NewOrderRequest &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::AmendOrderRequest &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::CancelOrderRequest &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::MassQuoteRequest &value) {
  // XXX
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::MassCancelRequest &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::MassQuoteCancelRequest &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::NewOrderResponse &value) {
  // XXX
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::NewOrderReject &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::AmendOrderResponse &value) {
  // XXX
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::AmendOrderReject &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::CancelOrderResponse &value) {
  // XXX
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::CancelOrderReject &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::MassQuoteResponse &value) {
  // XXX
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::MassQuoteReject &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::MassCancelResponse &value) {
  // XXX
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::MassCancelReject &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::OrderFilled &value) {
  // XXX
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::OrdersCanceled &value) {
  // XXX
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::OrderPlaced &value) {
  // XXX
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::MassQuoteOrdersPlaced &value) {
  // XXX
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::MassQuoteMmpTriggered &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::OrdersMmpTriggered &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::MassQuoteMmpUnfrozen &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::OrdersMmpUnfrozen &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_order::DummyMessage &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

// incremental

template <>
inline size_t compute_length(deribit_sbe_market_data::Instrument &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_market_data::TradingStatusUpdate &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_market_data::InstrumentInfo &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_market_data::InstrumentRef &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_market_data::BidPut &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_market_data::AskPut &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_market_data::BidQtyReduced &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_market_data::AskQtyReduced &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_market_data::BidDelete &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_market_data::AskDelete &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_market_data::TradeSummary &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_market_data::Trade &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_market_data::BlockTrade &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

// snapshot

template <>
inline size_t compute_length(deribit_sbe_market_data::SnapshotHeader &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_market_data::SnapshotTrailer &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_market_data::EndOfCycle &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

// retransmit

template <>
inline size_t compute_length(deribit_sbe_market_data::RetransmitRequest &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(deribit_sbe_market_data::RetransmitReject &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

}  // namespace sbe
}  // namespace starbase

template <>
inline constexpr std::string_view get_name<deribit_sbe_market_data::Instrument>() {
  using namespace std::literals;
  return "instrument"sv;
}

template <>
inline constexpr std::string_view get_name<deribit_sbe_market_data::TradingStatusUpdate>() {
  using namespace std::literals;
  return "trading_status_update"sv;
}

template <>
inline constexpr std::string_view get_name<deribit_sbe_market_data::InstrumentInfo>() {
  using namespace std::literals;
  return "instrument_info"sv;
}

template <>
inline constexpr std::string_view get_name<deribit_sbe_market_data::InstrumentRef>() {
  using namespace std::literals;
  return "instrument_ref"sv;
}

template <>
inline constexpr std::string_view get_name<deribit_sbe_market_data::BidPut>() {
  using namespace std::literals;
  return "bid_put"sv;
}

template <>
inline constexpr std::string_view get_name<deribit_sbe_market_data::AskPut>() {
  using namespace std::literals;
  return "ask_put"sv;
}

template <>
inline constexpr std::string_view get_name<deribit_sbe_market_data::BidQtyReduced>() {
  using namespace std::literals;
  return "bid_qty_reduced"sv;
}

template <>
inline constexpr std::string_view get_name<deribit_sbe_market_data::AskQtyReduced>() {
  using namespace std::literals;
  return "ask_qty_reduced"sv;
}

template <>
inline constexpr std::string_view get_name<deribit_sbe_market_data::BidDelete>() {
  using namespace std::literals;
  return "bid_delete"sv;
}

template <>
inline constexpr std::string_view get_name<deribit_sbe_market_data::AskDelete>() {
  using namespace std::literals;
  return "ask_delete"sv;
}

template <>
inline constexpr std::string_view get_name<deribit_sbe_market_data::TradeSummary>() {
  using namespace std::literals;
  return "trade_summary"sv;
}

template <>
inline constexpr std::string_view get_name<deribit_sbe_market_data::Trade>() {
  using namespace std::literals;
  return "trade"sv;
}

template <>
inline constexpr std::string_view get_name<deribit_sbe_market_data::BlockTrade>() {
  using namespace std::literals;
  return "block_trade"sv;
}

template <>
inline constexpr std::string_view get_name<deribit_sbe_market_data::SnapshotHeader>() {
  using namespace std::literals;
  return "snapshot_header"sv;
}

template <>
inline constexpr std::string_view get_name<deribit_sbe_market_data::SnapshotTrailer>() {
  using namespace std::literals;
  return "snapshot_trailer"sv;
}

template <>
inline constexpr std::string_view get_name<deribit_sbe_market_data::EndOfCycle>() {
  using namespace std::literals;
  return "end_of_cycle"sv;
}

template <>
inline constexpr std::string_view get_name<deribit_sbe_market_data::RetransmitRequest>() {
  using namespace std::literals;
  return "retransmit_request"sv;
}

template <>
inline constexpr std::string_view get_name<deribit_sbe_market_data::RetransmitReject>() {
  using namespace std::literals;
  return "retransmit_reject"sv;
}

}  // namespace roq

// composite

template <>
struct fmt::formatter<deribit_sbe_order::MessageHeader> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::MessageHeader &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(protocolId={}, )"
        R"(flags={}, )"
        R"(messageLength={}, )"
        R"(messageTypeId={}, )"
        R"(version={}, )"
        R"(sequenceNumber={}, )"
        R"(lastProcessedSeqNo={}, )"
        R"(sendTimeNs={})"
        R"(}})"sv,
        value.protocolId(),
        value.flags().rawValue(),
        value.messageLength(),
        value.messageTypeId(),
        value.version(),
        value.sequenceNumber(),
        value.lastProcessedSeqNo(),
        value.sendTimeNs());
  }
};

// types

template <>
struct fmt::formatter<deribit_sbe_order::Decimal72> {
  using value_type = deribit_sbe_order::Decimal72;
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(value_type const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(context.out(), R"({})"sv, roq::map(value).template get<double>());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::Price9> {
  using value_type = deribit_sbe_order::Price9;
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(value_type const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(context.out(), R"({})"sv, roq::map(value).template get<double>());
  }
};

// choice

template <>
struct fmt::formatter<deribit_sbe_order::MassQuoteFlags> {
  using value_type = deribit_sbe_order::MassQuoteFlags;
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(value_type const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(context.out(), R"({})"sv, value.rawValue());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::MultiPartEventFlags> {
  using value_type = deribit_sbe_order::MultiPartEventFlags;
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(value_type const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(context.out(), R"({})"sv, value.rawValue());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::OrderFlags> {
  using value_type = deribit_sbe_order::OrderFlags;
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(value_type const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(context.out(), R"({})"sv, value.rawValue());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::ReplaceOrderFlags> {
  using value_type = deribit_sbe_order::ReplaceOrderFlags;
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(value_type const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(context.out(), R"({})"sv, value.rawValue());
  }
};

// session

template <>
struct fmt::formatter<deribit_sbe_order::Logon> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::Logon &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(clientId="{}", )"
        R"(secret="{}", )"
        R"(resetSeqNum={})"
        R"(}})"sv,
        value.clientId(),
        value.secret(),
        value.resetSeqNum());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::LogonConf> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::LogonConf &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(heartbeatIntervalSeconds={})"
        R"(}})"sv,
        value.heartbeatIntervalSeconds());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::Logout> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::Logout &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(reason="{}")"
        R"(}})"sv,
        value.reason());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::LoggedOut> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::LoggedOut &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(reason="{}")"
        R"(}})"sv,
        value.reason());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::Heartbeat> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::Heartbeat &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(correlationId={})"
        R"(}})"sv,
        value.correlationId());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::TestRequest> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::TestRequest &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(correlationId={})"
        R"(}})"sv,
        value.correlationId());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::ResendRequest> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::ResendRequest &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(fromSequenceNumber={}, )"
        R"(toSequenceNumber={})"
        R"(}})"sv,
        value.fromSequenceNumber(),
        value.toSequenceNumber());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::GapFill> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::GapFill &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(newSequenceNumber={})"
        R"(}})"sv,
        value.newSequenceNumber());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::Reject> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::Reject &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(refSequenceNumber={}, )"
        R"(reason={}, )"
        R"(details="{}")"
        R"(}})"sv,
        value.refSequenceNumber(),
        value.reason(),
        value.details());
  }
};

// application

template <>
struct fmt::formatter<deribit_sbe_order::NewOrderRequest> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::NewOrderRequest &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(clientOrderId={}, )"
        R"(correlationId={}, )"
        R"(instrumentId={}, )"
        R"(price={}, )"
        R"(quantity={}, )"
        R"(showQty={}, )"
        R"(selfMatchPreventionId={}, )"
        R"(side={}, )"
        R"(timeInForce={}, )"
        R"(flags={}, )"
        R"(selfTradingMode={})"
        R"(}})"sv,
        value.clientOrderId(),
        value.correlationId(),
        value.instrumentId(),
        value.price(),
        value.quantity(),
        value.showQty(),
        value.selfMatchPreventionId(),
        value.side(),
        value.timeInForce(),
        value.flags(),
        value.selfTradingMode());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::AmendOrderRequest> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::AmendOrderRequest &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(clientOrderId={}, )"
        R"(correlationId={}, )"
        R"(instrumentId={}, )"
        R"(price={}, )"
        R"(quantity={}, )"
        R"(showQty={}, )"
        R"(flags={})"
        R"(}})"sv,
        value.clientOrderId(),
        value.correlationId(),
        value.instrumentId(),
        value.price(),
        value.quantity(),
        value.showQty(),
        value.flags());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::CancelOrderRequest> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::CancelOrderRequest &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(clientOrderId={}, )"
        R"(correlationId={}, )"
        R"(instrumentId={})"
        R"(}})"sv,
        value.clientOrderId(),
        value.correlationId(),
        value.instrumentId());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::MassQuoteRequest> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::MassQuoteRequest &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(quoteId={}, )"
        R"(correlationId={}, )"
        R"(mmpGroupId={}, )"
        R"(selfMatchPreventionId={}, )"
        R"(flags={}, )"
        R"(quotes=[XXX])"  // XXX
        R"(}})"sv,
        value.quoteId(),
        value.correlationId(),
        value.mmpGroupId(),
        value.selfMatchPreventionId(),
        value.flags());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::MassCancelRequest> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::MassCancelRequest &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(correlationId={}, )"
        R"(currencyPairId={}, )"
        R"(instrumentId={}, )"
        R"(productType={}, )"
        R"(side={})"
        R"(}})"sv,
        value.correlationId(),
        value.currencyPairId(),
        value.instrumentId(),
        value.productType(),
        value.side());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::MassQuoteCancelRequest> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::MassQuoteCancelRequest &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(correlationId={}, )"
        R"(mmpGroupId={}, )"
        R"(side={})"
        R"(}})"sv,
        value.correlationId(),
        value.mmpGroupId(),
        value.side());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::NewOrderResponse> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::NewOrderResponse &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(timestamp={}, )"
        R"(execId={}, )"
        R"(clientOrderId={}, )"
        R"(correlationId={}, )"
        R"(orderId={}, )"
        R"(instrumentId={}, )"
        R"(price={}, )"
        R"(quantity={}, )"
        R"(totalFilled={}, )"
        R"(visibleQty={}, )"
        R"(receiveTime={}, )"
        R"(side={}, )"
        R"(status={}, )"
        R"(cancelReason={}, )"
        R"(fills=[XXX], )"  // XXX
        R"(legs=[XXX])"     // XXX
        R"(}})"sv,
        value.timestamp(),
        value.execId(),
        value.clientOrderId(),
        value.correlationId(),
        value.orderId(),
        value.instrumentId(),
        value.price(),
        value.quantity(),
        value.totalFilled(),
        value.visibleQty(),
        value.receiveTime(),
        value.side(),
        value.status(),
        value.cancelReason());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::NewOrderReject> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::NewOrderReject &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(timestamp={}, )"
        R"(execId={}, )"
        R"(clientOrderId={}, )"
        R"(correlationId={}, )"
        R"(orderId={}, )"
        R"(instrumentId={}, )"
        R"(reason={}, )"
        R"(details={}, )"
        R"(}})"sv,
        value.timestamp(),
        value.execId(),
        value.clientOrderId(),
        value.correlationId(),
        value.orderId(),
        value.instrumentId(),
        value.reason(),
        value.details());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::AmendOrderResponse> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::AmendOrderResponse &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(timestamp={}, )"
        R"(execId={}, )"
        R"(clientOrderId={}, )"
        R"(correlationId={}, )"
        R"(orderId={}, )"
        R"(instrumentId={}, )"
        R"(price={}, )"
        R"(quantity={}, )"
        R"(totalFilled={}, )"
        R"(visibleQty={}, )"
        R"(receiveTime={}, )"
        R"(status={}, )"
        R"(cancelReason={}, )"
        R"(fills=[XXX], )"  // XXX
        R"(legs=[XXX])"     // XXX
        R"(}})"sv,
        value.timestamp(),
        value.execId(),
        value.clientOrderId(),
        value.correlationId(),
        value.orderId(),
        value.instrumentId(),
        value.price(),
        value.quantity(),
        value.totalFilled(),
        value.visibleQty(),
        value.receiveTime(),
        value.status(),
        value.cancelReason());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::AmendOrderReject> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::AmendOrderReject &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(timestamp={}, )"
        R"(execId={}, )"
        R"(clientOrderId={}, )"
        R"(correlationId={}, )"
        R"(orderId={}, )"
        R"(instrumentId={}, )"
        R"(reason={}, )"
        R"(details={}, )"
        R"(}})"sv,
        value.timestamp(),
        value.execId(),
        value.clientOrderId(),
        value.correlationId(),
        value.orderId(),
        value.instrumentId(),
        value.reason(),
        value.details());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::CancelOrderResponse> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::CancelOrderResponse &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(timestamp={}, )"
        R"(execId={}, )"
        R"(clientOrderId={}, )"
        R"(correlationId={}, )"
        R"(orderId={}, )"
        R"(instrumentId={}, )"
        R"(receiveTime={})"
        R"(}})"sv,
        value.timestamp(),
        value.execId(),
        value.clientOrderId(),
        value.correlationId(),
        value.orderId(),
        value.instrumentId(),
        value.receiveTime());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::CancelOrderReject> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::CancelOrderReject &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(timestamp={}, )"
        R"(execId={}, )"
        R"(clientOrderId={}, )"
        R"(correlationId={}, )"
        R"(orderId={}, )"
        R"(instrumentId={}, )"
        R"(reason={}, )"
        R"(details={}, )"
        R"(}})"sv,
        value.timestamp(),
        value.execId(),
        value.clientOrderId(),
        value.correlationId(),
        value.orderId(),
        value.instrumentId(),
        value.reason(),
        value.details());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::MassQuoteResponse> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::MassQuoteResponse &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(timestamp={}, )"
        R"(execId={}, )"
        R"(quoteId={}, )"
        R"(correlationId={}, )"
        R"(mmpGroupId={}, )"
        R"(receiveTime={}, )"
        R"(quotes=[XXX], )"    // XXX
        R"(bidFills=[XXX], )"  // XXX
        R"(askFills=[XXX], )"  // XXX
        R"(legs=[XXX])"        // XXX
        R"(}})"sv,
        value.timestamp(),
        value.execId(),
        value.quoteId(),
        value.correlationId(),
        value.mmpGroupId(),
        value.receiveTime());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::MassQuoteReject> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::MassQuoteReject &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(timestamp={}, )"
        R"(execId={}, )"
        R"(quoteId={}, )"
        R"(correlationId={}, )"
        R"(mmpGroupId={}, )"
        R"(reason={}, )"
        R"(details={}, )"
        R"(}})"sv,
        value.timestamp(),
        value.execId(),
        value.quoteId(),
        value.correlationId(),
        value.mmpGroupId(),
        value.reason(),
        value.details());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::MassCancelResponse> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::MassCancelResponse &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(timestamp={}, )"
        R"(execId={}, )"
        R"(correlationId={}, )"
        R"(receiveTime={}, )"
        R"(totalOrderCount={})"
        R"(}})"sv,
        value.timestamp(),
        value.execId(),
        value.correlationId(),
        value.receiveTime(),
        value.totalOrderCount());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::MassCancelReject> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::MassCancelReject &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(timestamp={}, )"
        R"(execId={}, )"
        R"(correlationId={}, )"
        R"(reason={}, )"
        R"(details="{}")"
        R"(}})"sv,
        value.timestamp(),
        value.execId(),
        value.correlationId(),
        value.reason(),
        value.details());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::OrderFilled> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::OrderFilled &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(timestamp={}, )"
        R"(execId={}, )"
        R"(fills=[XXX], )"  // XXX
        R"(legs=[XXX])"     // XXX
        R"(}})"sv,
        value.timestamp(),
        value.execId());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::OrdersCanceled> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::OrdersCanceled &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(timestamp={}, )"
        R"(execId={}, )"
        R"(flags={}, )"
        R"(orders=[XXX])"  // XXX
        R"(}})"sv,
        value.timestamp(),
        value.execId(),
        value.flags());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::OrderPlaced> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::OrderPlaced &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(timestamp={}, )"
        R"(execId={}, )"
        R"(clientOrderId={}, )"
        R"(orderId={}, )"
        R"(instrumentId={}, )"
        R"(price={}, )"
        R"(quantity={}, )"
        R"(totalFilled={}, )"
        R"(visibleQty={}, )"
        R"(status={}, )"
        R"(cancelReason={}, )"
        R"(fills=[XXX], )"  // XXX
        R"(legs=[XXX])"     // XXX
        R"(}})"sv,
        value.timestamp(),
        value.execId(),
        value.clientOrderId(),
        value.orderId(),
        value.instrumentId(),
        value.price(),
        value.quantity(),
        value.totalFilled(),
        value.visibleQty(),
        value.status(),
        value.cancelReason());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::MassQuoteOrdersPlaced> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::MassQuoteOrdersPlaced &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(timestamp={}, )"
        R"(execId={}, )"
        R"(mmpGroupId={}, )"
        R"(orders=[XXX], )"  // XXX
        R"(fills=[XXX], )"   // XXX
        R"(legs=[XXX])"      // XXX
        R"(}})"sv,
        value.timestamp(),
        value.execId(),
        value.mmpGroupId());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::MassQuoteMmpTriggered> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::MassQuoteMmpTriggered &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(timestamp={}, )"
        R"(execId={}, )"
        R"(mmpGroupId={}, )"
        R"(frozenUntil={}, )"
        R"(quantityLevel={}, )"
        R"(vegaLevel={}, )"
        R"(deltaLevel={}, )"
        R"(trigger={})"
        R"(}})"sv,
        value.timestamp(),
        value.execId(),
        value.mmpGroupId(),
        value.frozenUntil(),
        value.quantityLevel(),
        value.vegaLevel(),
        value.deltaLevel(),
        value.trigger());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::OrdersMmpTriggered> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::OrdersMmpTriggered &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(timestamp={}, )"
        R"(execId={}, )"
        R"(currencyPairId={}, )"
        R"(frozenUntil={}, )"
        R"(quantityLevel={}, )"
        R"(vegaLevel={}, )"
        R"(deltaLevel={}, )"
        R"(trigger={})"
        R"(}})"sv,
        value.timestamp(),
        value.execId(),
        value.currencyPairId(),
        value.frozenUntil(),
        value.quantityLevel(),
        value.vegaLevel(),
        value.deltaLevel(),
        value.trigger());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::MassQuoteMmpUnfrozen> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::MassQuoteMmpUnfrozen &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(timestamp={}, )"
        R"(execId={}, )"
        R"(mmpGroupId={}, )"
        R"(correlationId={})"
        R"(}})"sv,
        value.timestamp(),
        value.execId(),
        value.mmpGroupId(),
        value.correlationId());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::OrdersMmpUnfrozen> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::OrdersMmpUnfrozen &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(timestamp={}, )"
        R"(execId={}, )"
        R"(currencyPairId={}, )"
        R"(correlationId={})"
        R"(}})"sv,
        value.timestamp(),
        value.execId(),
        value.currencyPairId(),
        value.correlationId());
  }
};

template <>
struct fmt::formatter<deribit_sbe_order::DummyMessage> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_order::DummyMessage &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(header={})"
        R"(}})"sv,
        value.header());
  }
};

//

template <>
struct fmt::formatter<deribit_sbe_market_data::MdMessageHeader> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::MdMessageHeader &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(messageLength={}, )"
        R"(templateId={}, )"
        R"(version={}, )"
        R"(flags={}, )"
        R"(transactTime={})"
        R"(}})"sv,
        value.messageLength(),
        value.templateId(),
        value.version(),
        value.flags().rawValue(),
        value.transactTime());
  }
};

// composite

template <>
struct fmt::formatter<deribit_sbe_market_data::LogicalExpiry> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::LogicalExpiry &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(year={}, )"
        R"(month={}, )"
        R"(weekOfMonth={}, )"
        R"(dayOfMonth={})"
        R"(}})"sv,
        value.year(),
        value.month(),
        value.weekOfMonth(),
        value.dayOfMonth());
  }
};

// types

template <>
struct fmt::formatter<deribit_sbe_market_data::Price9> {
  using value_type = deribit_sbe_market_data::Price9;
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(value_type const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(context.out(), R"({})"sv, roq::map(value).template get<double>());
  }
};

// choice

template <>
struct fmt::formatter<deribit_sbe_market_data::InstrumentFlags> {
  using value_type = deribit_sbe_market_data::InstrumentFlags;
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(value_type const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(context.out(), R"({})"sv, value.rawValue());
  }
};

template <>
struct fmt::formatter<deribit_sbe_market_data::TradeFlags> {
  using value_type = deribit_sbe_market_data::TradeFlags;
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(value_type const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(context.out(), R"({})"sv, value.rawValue());
  }
};

// incremental

template <>
struct fmt::formatter<deribit_sbe_market_data::Instrument> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::Instrument &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    auto creation_time = roq::Map{value.creationTime(), value.creationTimeNullValue()}.template get<std::chrono::nanoseconds>();
    auto expiry_time = roq::Map{value.expiryTime(), value.expiryTimeNullValue()}.template get<std::chrono::nanoseconds>();
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(instrumentId={}, )"
        R"(symbol="{}", )"
        R"(name="{}", )"
        R"(baseCurrency="{}", )"
        R"(quoteCurrency="{}", )"
        R"(baseIncrement={}, )"
        R"(tickSize={}, )"
        R"(strikePrice={}, )"
        R"(largeTickSize0={}, )"
        R"(largeTickThreshold0={}, )"
        R"(largeTickSize1={}, )"
        R"(largeTickThreshold1={}, )"
        R"(creationTime={}, )"
        R"(expiryTime={}, )"
        R"(logicalExpiry={}, )"
        R"(flags={}, )"
        R"(type={}, )"
        R"(status={}, )"
        R"(quantityExponent={})"
        R"(}})"sv,
        value.instrumentId(),
        value.symbol(),
        value.name(),
        value.baseCurrency(),
        value.quoteCurrency(),
        value.baseIncrement(),
        value.tickSize(),
        value.strikePrice(),
        value.largeTickSize0(),
        value.largeTickThreshold0(),
        value.largeTickSize1(),
        value.largeTickThreshold1(),
        creation_time,
        expiry_time,
        value.logicalExpiry(),
        value.flags(),
        value.type(),
        value.status(),
        value.quantityExponent());
  }
};

template <>
struct fmt::formatter<deribit_sbe_market_data::TradingStatusUpdate> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::TradingStatusUpdate &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(instrumentId={}, )"
        R"(tradingStatus={})"
        R"(}})"sv,
        value.instrumentId(),
        value.tradingStatus());
  }
};

template <>
struct fmt::formatter<deribit_sbe_market_data::InstrumentInfo> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::InstrumentInfo &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(instrumentId={}, )"
        R"(minSellPrice={}, )"
        R"(maxBuyPrice={}, )"
        R"(indexPrice={}, )"
        R"(markPrice={})"
        R"(}})"sv,
        value.instrumentId(),
        value.minSellPrice(),
        value.maxBuyPrice(),
        value.indexPrice(),
        value.markPrice());
  }
};

template <>
struct fmt::formatter<deribit_sbe_market_data::InstrumentRef> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::InstrumentRef &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(instrumentId={}, )"
        R"(currentFunding={}, )"
        R"(funding8h={}, )"
        R"(estimatedDeliveryPrice={}, )"
        R"(deliveryPrice={}, )"
        R"(settlementPrice={})"
        R"(}})"sv,
        value.instrumentId(),
        value.currentFunding(),
        value.funding8h(),
        value.estimatedDeliveryPrice(),
        value.deliveryPrice(),
        value.settlementPrice());
  }
};

template <>
struct fmt::formatter<deribit_sbe_market_data::BidPut> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::BidPut &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(orderId={}, )"
        R"(instrumentId={}, )"
        R"(quantityMantissa={}, )"
        R"(price={})"
        R"(}})"sv,
        value.orderId(),
        value.instrumentId(),
        value.quantityMantissa(),
        value.price());
  }
};

template <>
struct fmt::formatter<deribit_sbe_market_data::AskPut> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::AskPut &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(orderId={}, )"
        R"(instrumentId={}, )"
        R"(quantityMantissa={}, )"
        R"(price={})"
        R"(}})"sv,
        value.orderId(),
        value.instrumentId(),
        value.quantityMantissa(),
        value.price());
  }
};

template <>
struct fmt::formatter<deribit_sbe_market_data::AskQtyReduced> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::AskQtyReduced &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(orderId={}, )"
        R"(instrumentId={}, )"
        R"(quantityMantissa={})"
        R"(}})"sv,
        value.orderId(),
        value.instrumentId(),
        value.quantityMantissa());
  }
};

template <>
struct fmt::formatter<deribit_sbe_market_data::BidQtyReduced> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::BidQtyReduced &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(orderId={}, )"
        R"(instrumentId={}, )"
        R"(quantityMantissa={})"
        R"(}})"sv,
        value.orderId(),
        value.instrumentId(),
        value.quantityMantissa());
  }
};

template <>
struct fmt::formatter<deribit_sbe_market_data::BidDelete> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::BidDelete &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(orderId={}, )"
        R"(instrumentId={})"
        R"(}})"sv,
        value.orderId(),
        value.instrumentId());
  }
};

template <>
struct fmt::formatter<deribit_sbe_market_data::AskDelete> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::AskDelete &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(orderId={}, )"
        R"(instrumentId={})"
        R"(}})"sv,
        value.orderId(),
        value.instrumentId());
  }
};

template <>
struct fmt::formatter<deribit_sbe_market_data::TradeSummary> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::TradeSummary &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(instrumentId={}, )"
        R"(takerOrderId={}, )"
        R"(totalFilledMantissa={}, )"
        R"(deepestPrice={}, )"
        R"(markPrice={}, )"
        R"(indexPrice={}, )"
        R"(impliedVolatility={}, )"
        R"(takerFlags={})"
        R"(}})"sv,
        value.instrumentId(),
        value.takerOrderId(),
        value.totalFilledMantissa(),
        value.deepestPrice(),
        value.markPrice(),
        value.indexPrice(),
        value.impliedVolatility(),
        value.takerFlags());
  }
};

template <>
struct fmt::formatter<deribit_sbe_market_data::Trade> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::Trade &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(matchId={}, )"
        R"(instrumentId={}, )"
        R"(makerOrderId={}, )"
        R"(fillQtyMantissa={}, )"
        R"(fillPrice={}, )"
        R"(makerFlags={})"
        R"(}})"sv,
        value.matchId(),
        value.instrumentId(),
        value.makerOrderId(),
        value.fillQtyMantissa(),
        value.fillPrice(),
        value.makerFlags());
  }
};

template <>
struct fmt::formatter<deribit_sbe_market_data::BlockTrade> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::BlockTrade &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(matchId={}, )"
        R"(instrumentId={}, )"
        R"(blockTradeId={}, )"
        R"(blockRfqId={}, )"
        R"(fillQtyMantissa={}, )"
        R"(fillPrice={}, )"
        R"(markPrice={}, )"
        R"(indexPrice={}, )"
        R"(impliedVolatility={}, )"
        R"(takerFlags={}, )"
        R"(numberOfLegs={})"
        R"(}})"sv,
        value.matchId(),
        value.instrumentId(),
        value.blockTradeId(),
        value.blockRfqId(),
        value.fillQtyMantissa(),
        value.fillPrice(),
        value.markPrice(),
        value.indexPrice(),
        value.impliedVolatility(),
        value.takerFlags(),
        value.numberOfLegs());
  }
};

template <>
struct fmt::formatter<deribit_sbe_market_data::SnapshotHeader> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::SnapshotHeader &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(instrumentId={}, )"
        R"(incrementalTimestamp={}, )"
        R"(incrementalSeqNum={})"
        R"(}})"sv,
        value.instrumentId(),
        value.incrementalTimestamp(),
        value.incrementalSeqNum());
  }
};

template <>
struct fmt::formatter<deribit_sbe_market_data::SnapshotTrailer> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::SnapshotTrailer &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(instrumentId={}, )"
        R"(timestamp={}, )"
        R"(incrementSeqNum={})"
        R"(}})"sv,
        value.instrumentId(),
        value.timestamp(),
        value.incrementSeqNum());
  }
};

template <>
struct fmt::formatter<deribit_sbe_market_data::EndOfCycle> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::EndOfCycle &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(activeInstrumentCount={})"
        R"(}})"sv,
        value.activeInstrumentCount());
  }
};

template <>
struct fmt::formatter<deribit_sbe_market_data::RetransmitRequest> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::RetransmitRequest &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(beginSeqNum={}, )"
        R"(messagecount={})"
        R"(}})"sv,
        value.beginSeqNum(),
        value.messageCount());
  }
};

template <>
struct fmt::formatter<deribit_sbe_market_data::RetransmitReject> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(deribit_sbe_market_data::RetransmitReject &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(retryDelayNanos={}, )"
        R"(details="{}", )"
        R"(reason={})"
        R"(}})"sv,
        value.retryDelayNanos(),
        value.details(),
        value.reason());
  }
};
