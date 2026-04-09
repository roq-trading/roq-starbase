/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <fmt/chrono.h>
#include <fmt/format.h>

#include <magic_enum/magic_enum_format.hpp>

#include <starbase_sbe/BookChange.h>
#include <starbase_sbe/BookSide.h>
#include <starbase_sbe/Direction.h>
#include <starbase_sbe/InstrumentState.h>
#include <starbase_sbe/Liquidation.h>
#include <starbase_sbe/YesNo.h>

#include <starbase_sbe/Book.h>           // 1001
#include <starbase_sbe/ComboLegs.h>      // 1007
#include <starbase_sbe/Instrument.h>     // 1000
#include <starbase_sbe/InstrumentV2.h>   // 1010
#include <starbase_sbe/PriceIndex.h>     // 1008
#include <starbase_sbe/Rfq.h>            // 1009
#include <starbase_sbe/Snapshot.h>       // 1004
#include <starbase_sbe/SnapshotEnd.h>    // 1006
#include <starbase_sbe/SnapshotStart.h>  // 1005
#include <starbase_sbe/Ticker.h>         // 1003
#include <starbase_sbe/Trades.h>         // 1002

#include "roq/api.hpp"

#include "roq/core/sbe/iterator.hpp"

#include "roq/starbase/sbe/map.hpp"

namespace roq {
namespace starbase {
namespace sbe {

template <typename T>
size_t compute_length(T &);

template <>
inline size_t compute_length(starbase_sbe::Book &value) {
  auto changes_list_length = value.changesList().count();
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength(changes_list_length);
}

template <>
inline size_t compute_length(starbase_sbe::ComboLegs &value) {
  auto legs_list_length = value.legsList().count();
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength(legs_list_length);
}

template <>
inline size_t compute_length(starbase_sbe::Instrument &value) {
  auto instrument_name_length = value.instrumentNameLength();
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength(instrument_name_length);
}

template <>
inline size_t compute_length(starbase_sbe::InstrumentV2 &value) {
  value.sbeRewind();
  size_t tick_steps_list_length = 0;
  value.tickStepsList().forEach([&]([[maybe_unused]] auto &item) { ++tick_steps_list_length; });  // note!
  auto instrument_name_length = value.instrumentNameLength();
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength(tick_steps_list_length, instrument_name_length);
}

template <>
inline size_t compute_length(starbase_sbe::PriceIndex &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(starbase_sbe::Rfq &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(starbase_sbe::Snapshot &value) {
  auto levels_list_length = value.levelsList().count();
  value.sbeRewind();  // note!
  value.levelsList().forEach([](auto &item) { item.skip(); });
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength(levels_list_length);
}

template <>
inline size_t compute_length(starbase_sbe::SnapshotStart &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(starbase_sbe::SnapshotEnd &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(starbase_sbe::Ticker &value) {
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength();
}

template <>
inline size_t compute_length(starbase_sbe::Trades &value) {
  auto trades_list_length = value.tradesList().count();
  using value_type = std::remove_cvref_t<decltype(value)>;
  return value_type::computeLength(trades_list_length);
}

// sbe weirdness ...

template <typename T>
std::string get_instrument_name(T &);

template <>
inline std::string get_instrument_name(starbase_sbe::Instrument &value) {
  value.sbeRewind();                           // note!
  auto length = value.instrumentNameLength();  // must fetch before getting name
  return {value.instrumentName(), length};
}

template <>
inline std::string get_instrument_name(starbase_sbe::InstrumentV2 &value) {
  value.sbeRewind();                                                   // note!
  value.tickStepsList().forEach([&]([[maybe_unused]] auto &item) {});  // note!
  auto length = value.instrumentNameLength();                          // must fetch before getting name
  return {value.instrumentName(), length};
}

}  // namespace sbe
}  // namespace starbase

template <>
constexpr std::string_view get_name<starbase_sbe::Book>() {
  using namespace std::literals;
  return "book"sv;
}

template <>
constexpr std::string_view get_name<starbase_sbe::ComboLegs>() {
  using namespace std::literals;
  return "combo_legs"sv;
}

template <>
constexpr std::string_view get_name<starbase_sbe::Instrument>() {
  using namespace std::literals;
  return "instrument"sv;
}

template <>
constexpr std::string_view get_name<starbase_sbe::InstrumentV2>() {
  using namespace std::literals;
  return "instrument_v2"sv;
}

template <>
constexpr std::string_view get_name<starbase_sbe::PriceIndex>() {
  using namespace std::literals;
  return "price_index"sv;
}

template <>
constexpr std::string_view get_name<starbase_sbe::Rfq>() {
  using namespace std::literals;
  return "rfq"sv;
}

template <>
constexpr std::string_view get_name<starbase_sbe::Snapshot>() {
  using namespace std::literals;
  return "snapshot"sv;
}

template <>
constexpr std::string_view get_name<starbase_sbe::SnapshotEnd>() {
  using namespace std::literals;
  return "snapshot_end"sv;
}

template <>
constexpr std::string_view get_name<starbase_sbe::SnapshotStart>() {
  using namespace std::literals;
  return "snapshot_start"sv;
}

template <>
constexpr std::string_view get_name<starbase_sbe::Ticker>() {
  using namespace std::literals;
  return "ticker"sv;
}

template <>
constexpr std::string_view get_name<starbase_sbe::Trades>() {
  using namespace std::literals;
  return "trades"sv;
}
}  // namespace roq

// helper

template <>
struct fmt::formatter<starbase_sbe::Book::ChangesList> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(starbase_sbe::Book::ChangesList const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(side={}, )"
        R"(change={}, )"
        R"(price={}, )"
        R"(amount={})"
        R"(}})"sv,
        starbase_sbe::BookSide::c_str(value.side()),
        starbase_sbe::BookChange::c_str(value.change()),
        value.price(),
        value.amount());
  }
};

template <>
struct fmt::formatter<starbase_sbe::ComboLegs::LegsList> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(starbase_sbe::ComboLegs::LegsList const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(instrumentId={}, )"
        R"(legSize={})"
        R"(}})"sv,
        value.legInstrumentId(),
        value.legSize());
  }
};

template <>
struct fmt::formatter<starbase_sbe::InstrumentV2::TickStepsList> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(starbase_sbe::InstrumentV2::TickStepsList const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(abovePrice={}, )"
        R"(tickSize={})"
        R"(}})"sv,
        value.abovePrice(),
        value.tickSize());
  }
};

template <>
struct fmt::formatter<starbase_sbe::Snapshot::LevelsList> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(starbase_sbe::Snapshot::LevelsList const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(side={}, )"
        R"(price={}, )"
        R"(amount={})"
        R"(}})"sv,
        starbase_sbe::BookSide::c_str(value.side()),
        value.price(),
        value.amount());
  }
};

template <>
struct fmt::formatter<starbase_sbe::Trades::TradesList> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(starbase_sbe::Trades::TradesList const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(direction={}, )"
        R"(price={}, )"
        R"(amount={}, )"
        R"(timestampMs={}, )"
        R"(markPrice={}, )"
        R"(indexPrice={}, )"
        R"(tradeSeq={}, )"
        R"(tradeId={}, )"
        R"(tickDirection={}, )"
        R"(liquidation={}, )"
        R"(iv={}, )"
        R"(blockTradeId={}, )"
        R"(comboTradeId={})"
        R"(}})"sv,
        starbase_sbe::Direction::c_str(value.direction()),
        value.price(),
        value.amount(),
        std::chrono::milliseconds{value.timestampMs()},
        value.markPrice(),
        value.indexPrice(),
        value.tradeSeq(),
        value.tradeId(),
        starbase_sbe::TickDirection::c_str(value.tickDirection()),
        starbase_sbe::Liquidation::c_str(value.liquidation()),
        value.iv(),
        value.blockTradeId(),
        value.comboTradeId());
  }
};

// messages
//
// note! some nested objects (lists) imply non-const due to positional information

template <>
struct fmt::formatter<starbase_sbe::Book> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(starbase_sbe::Book &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(instrumentId={}, )"
        R"(timestampMs={}, )"
        R"(prevChangeId={}, )"
        R"(changeId={}, )"
        R"(isLast={}, )"
        R"(changesList=[{}])"
        R"(}})"sv,
        value.instrumentId(),
        std::chrono::milliseconds{value.timestampMs()},
        value.prevChangeId(),
        value.changeId(),
        static_cast<bool>(roq::map(value.isLast())),
        fmt::join(roq::core::sbe::iterator{value.changesList()}, roq::core::sbe::sentinel{}, ", "sv));
  }
};

template <>
struct fmt::formatter<starbase_sbe::ComboLegs> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(starbase_sbe::ComboLegs &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(instrumentId={}, )"
        R"(legsList=[{}])"
        R"(}})"sv,
        value.instrumentId(),
        fmt::join(roq::core::sbe::iterator{value.legsList()}, roq::core::sbe::sentinel{}, ", "sv));
  }
};

template <>
struct fmt::formatter<starbase_sbe::Instrument> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(starbase_sbe::Instrument &value, format_context &context) const {
    using namespace std::literals;
    auto instrument_name = roq::starbase::sbe::get_instrument_name(value);
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(instrumentId={}, )"
        R"(instrumentState={}, )"
        R"(kind={}, )"
        R"(instrumentType={}, )"
        R"(optionType={}, )"
        R"(rfq={}, )"
        R"(settlementPeriod={}, )"
        R"(settlementPeriodCount={}, )"
        R"(baseCurrency="{}", )"
        R"(quoteCurrency="{}", )"
        R"(counterCurrency="{}", )"
        R"(settlementCurrency="{}", )"
        R"(sizeCurrency="{}", )"
        R"(creationTimestampMs={}, )"
        R"(expirationTimestampMs={}, )"
        R"(strikePrice={}, )"
        R"(contractSize={}, )"
        R"(minTradeAmount={}, )"
        R"(tickSize={}, )"
        R"(makerCommission={}, )"
        R"(takerCommission={}, )"
        R"(blockTradeCommission={}, )"
        R"(maxLiquidationCommission={}, )"
        R"(maxLeverage={}, )"
        R"(instrumentName="{}")"
        R"(}})"sv,
        value.instrumentId(),
        starbase_sbe::InstrumentState::c_str(value.instrumentState()),
        starbase_sbe::InstrumentKind::c_str(value.kind()),
        starbase_sbe::InstrumentType::c_str(value.instrumentType()),
        starbase_sbe::OptionType::c_str(value.optionType()),
        static_cast<bool>(roq::map(value.rfq())),
        starbase_sbe::Period::c_str(value.settlementPeriod()),
        value.settlementPeriodCount(),
        value.baseCurrency(),
        value.quoteCurrency(),
        value.counterCurrency(),
        value.settlementCurrency(),
        value.sizeCurrency(),
        std::chrono::milliseconds{value.creationTimestampMs()},
        std::chrono::milliseconds{value.expirationTimestampMs()},
        value.strikePrice(),
        value.contractSize(),
        value.minTradeAmount(),
        value.tickSize(),
        value.makerCommission(),
        value.takerCommission(),
        value.blockTradeCommission(),
        value.maxLiquidationCommission(),
        value.maxLeverage(),
        instrument_name);
  }
};

template <>
struct fmt::formatter<starbase_sbe::InstrumentV2> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(starbase_sbe::InstrumentV2 &value, format_context &context) const {
    using namespace std::literals;
    auto instrument_name = roq::starbase::sbe::get_instrument_name(value);
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(instrumentId={}, )"
        R"(instrumentState={}, )"
        R"(kind={}, )"
        R"(instrumentType={}, )"
        R"(optionType={}, )"
        R"(settlementPeriod={}, )"
        R"(settlementPeriodCount={}, )"
        R"(baseCurrency="{}", )"
        R"(quoteCurrency="{}", )"
        R"(counterCurrency="{}", )"
        R"(settlementCurrency="{}", )"
        R"(sizeCurrency="{}", )"
        R"(creationTimestampMs={}, )"
        R"(expirationTimestampMs={}, )"
        R"(strikePrice={}, )"
        R"(contractSize={}, )"
        R"(minTradeAmount={}, )"
        R"(tickSize={}, )"
        R"(makerCommission={}, )"
        R"(takerCommission={}, )"
        R"(blockTradeCommission={}, )"
        R"(maxLiquidationCommission={}, )"
        R"(maxLeverage={}, )"
        R"(tickStepsList=[{}], )"
        R"(instrumentName="{}")"
        R"(}})"sv,
        value.instrumentId(),
        starbase_sbe::InstrumentState::c_str(value.instrumentState()),
        starbase_sbe::InstrumentKind::c_str(value.kind()),
        starbase_sbe::InstrumentType::c_str(value.instrumentType()),
        starbase_sbe::OptionType::c_str(value.optionType()),
        starbase_sbe::Period::c_str(value.settlementPeriod()),
        value.settlementPeriodCount(),
        value.baseCurrency(),
        value.quoteCurrency(),
        value.counterCurrency(),
        value.settlementCurrency(),
        value.sizeCurrency(),
        std::chrono::milliseconds{value.creationTimestampMs()},
        std::chrono::milliseconds{value.expirationTimestampMs()},
        value.strikePrice(),
        value.contractSize(),
        value.minTradeAmount(),
        value.tickSize(),
        value.makerCommission(),
        value.takerCommission(),
        value.blockTradeCommission(),
        value.maxLiquidationCommission(),
        value.maxLeverage(),
        fmt::join(roq::core::sbe::iterator{value.tickStepsList()}, roq::core::sbe::sentinel{}, ", "sv),
        instrument_name);
  }
};

template <>
struct fmt::formatter<starbase_sbe::Ticker> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(starbase_sbe::Ticker &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(instrumentId={}, )"
        R"(instrumentState={}, )"
        R"(timestampMs={}, )"
        R"(openInterest={}, )"
        R"(minSellPrice={}, )"
        R"(maxBuyPrice={}, )"
        R"(lastPrice={}, )"
        R"(indexPrice={}, )"
        R"(markPrice={}, )"
        R"(bestBidPrice={}, )"
        R"(bestBidAmount={}, )"
        R"(bestAskPrice={}, )"
        R"(bestAskAmount={}, )"
        R"(currentFunding={}, )"
        R"(funding8h={}, )"
        R"(estimatedDeliveryPrice={}, )"
        R"(deliveryPrice={}, )"
        R"(settlementPrice={})"
        R"(}})"sv,
        value.instrumentId(),
        starbase_sbe::InstrumentState::c_str(value.instrumentState()),
        std::chrono::milliseconds{value.timestampMs()},
        value.openInterest(),
        value.minSellPrice(),
        value.maxBuyPrice(),
        value.lastPrice(),
        value.indexPrice(),
        value.markPrice(),
        value.bestBidPrice(),
        value.bestBidAmount(),
        value.bestAskPrice(),
        value.bestAskAmount(),
        value.currentFunding(),
        value.funding8h(),
        value.estimatedDeliveryPrice(),
        value.deliveryPrice(),
        value.settlementPrice());
  }
};

template <>
struct fmt::formatter<starbase_sbe::PriceIndex> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(starbase_sbe::PriceIndex &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(indexName="{}", )"
        R"(price={}, )"
        R"(timestampMs={})"
        R"(}})"sv,
        value.indexName(),
        value.price(),
        std::chrono::milliseconds{value.timestampMs()});
  }
};

template <>
struct fmt::formatter<starbase_sbe::Rfq> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(starbase_sbe::Rfq &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(instrumentId={}, )"
        R"(state={}, )"
        R"(side={}, )"
        R"(amount={}, )"
        R"(timestampMs={})"
        R"(}})"sv,
        value.instrumentId(),
        static_cast<bool>(roq::map(value.state())),
        starbase_sbe::RfqDirection::c_str(value.side()),
        value.amount(),
        std::chrono::milliseconds{value.timestampMs()});
  }
};

template <>
struct fmt::formatter<starbase_sbe::Snapshot> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(starbase_sbe::Snapshot &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(instrumentId={}, )"
        R"(timestampMs={}, )"
        R"(changeId={}, )"
        R"(isBookComplete={}, )"
        R"(isLastInBook={}, )"
        R"(levelsList=[{}])"
        R"(}})"sv,
        value.instrumentId(),
        std::chrono::milliseconds{value.timestampMs()},
        value.changeId(),
        static_cast<bool>(roq::map(value.isBookComplete())),
        static_cast<bool>(roq::map(value.isLastInBook())),
        fmt::join(roq::core::sbe::iterator{value.levelsList()}, roq::core::sbe::sentinel{}, ", "sv));
  }
};

template <>
struct fmt::formatter<starbase_sbe::SnapshotStart> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(starbase_sbe::SnapshotStart &value, format_context &context) const {
    using namespace std::literals;
    value.sbeRewind();  // note!
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(snapshotDelay={})"
        R"(}})"sv,
        value.snapshotDelay());
  }
};

template <>
struct fmt::formatter<starbase_sbe::SnapshotEnd> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(starbase_sbe::SnapshotEnd &, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(context.out(), "{{}}"sv);
  }
};

template <>
struct fmt::formatter<starbase_sbe::Trades> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(starbase_sbe::Trades &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(instrumentId={}, )"
        R"(tradesList=[{}])"
        R"(}})"sv,
        value.instrumentId(),
        fmt::join(roq::core::sbe::iterator{value.tradesList()}, roq::core::sbe::sentinel{}, ", "sv));
  }
};
