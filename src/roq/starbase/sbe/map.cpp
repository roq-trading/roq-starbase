/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/sbe/map.hpp"

using namespace std::literals;

namespace roq {

namespace {
template <typename... Args>
using Helper = detail::MapHelper<Args...>;
}

// starbase => roq

// starbase_sbe::BookSide::Value => roq::Side

template <>
template <>
constexpr Helper<starbase_sbe::BookSide::Value>::operator std::optional<Side>() const {
  switch (std::get<0>(args_)) {
    using enum starbase_sbe::BookSide::Value;
    case ask:
      return Side::SELL;
    case bid:
      return Side::BUY;
    case NULL_VALUE:
      return Side::UNDEFINED;
  }
  return {};
}

static_assert(Helper{starbase_sbe::BookSide::Value{starbase_sbe::BookSide::ask}} == roq::Side::SELL);
static_assert(Helper{starbase_sbe::BookSide::Value{starbase_sbe::BookSide::bid}} == roq::Side::BUY);
static_assert(Helper{starbase_sbe::BookSide::Value{starbase_sbe::BookSide::NULL_VALUE}} == roq::Side::UNDEFINED);

template <>
template <>
std::optional<Side> Map<starbase_sbe::BookSide::Value>::helper() const {
  return Helper{args_};
}

// starbase_sbe::Direction::Value => roq::Side

template <>
template <>
constexpr Helper<starbase_sbe::Direction::Value>::operator std::optional<Side>() const {
  switch (std::get<0>(args_)) {
    using enum starbase_sbe::Direction::Value;
    case buy:
      return Side::BUY;
    case sell:
      return Side::SELL;
    case NULL_VALUE:
      return Side::UNDEFINED;
  }
  return {};
}

static_assert(Helper{starbase_sbe::Direction::Value{starbase_sbe::Direction::buy}} == roq::Side::BUY);
static_assert(Helper{starbase_sbe::Direction::Value{starbase_sbe::Direction::sell}} == roq::Side::SELL);
static_assert(Helper{starbase_sbe::Direction::Value{starbase_sbe::Direction::NULL_VALUE}} == roq::Side::UNDEFINED);

template <>
template <>
std::optional<Side> Map<starbase_sbe::Direction::Value>::helper() const {
  return Helper{args_};
}

// starbase_sbe::InstrumentState::Value => roq::TradingStatus

template <>
template <>
constexpr Helper<starbase_sbe::InstrumentState::Value>::operator std::optional<TradingStatus>() const {
  switch (std::get<0>(args_)) {
    using enum starbase_sbe::InstrumentState::Value;
    case created:
      return TradingStatus::OPEN;  // ???
    case open:
      return TradingStatus::OPEN;
    case closed:
      return TradingStatus::CLOSE;
    case settled:
      return TradingStatus::UNDEFINED;
    case inactive:
      return TradingStatus::UNDEFINED;
    case started:
      return TradingStatus::UNDEFINED;
    case deactivated:
      return TradingStatus::UNDEFINED;
    case NULL_VALUE:
      return TradingStatus::UNDEFINED;
  }
  return {};
}

static_assert(Helper{starbase_sbe::InstrumentState::Value{starbase_sbe::InstrumentState::created}} == roq::TradingStatus::OPEN);
static_assert(Helper{starbase_sbe::InstrumentState::Value{starbase_sbe::InstrumentState::open}} == roq::TradingStatus::OPEN);
static_assert(Helper{starbase_sbe::InstrumentState::Value{starbase_sbe::InstrumentState::closed}} == roq::TradingStatus::CLOSE);
static_assert(Helper{starbase_sbe::InstrumentState::Value{starbase_sbe::InstrumentState::settled}} == roq::TradingStatus::UNDEFINED);
static_assert(Helper{starbase_sbe::InstrumentState::Value{starbase_sbe::InstrumentState::inactive}} == roq::TradingStatus::UNDEFINED);
static_assert(Helper{starbase_sbe::InstrumentState::Value{starbase_sbe::InstrumentState::started}} == roq::TradingStatus::UNDEFINED);
static_assert(Helper{starbase_sbe::InstrumentState::Value{starbase_sbe::InstrumentState::deactivated}} == roq::TradingStatus::UNDEFINED);
static_assert(Helper{starbase_sbe::InstrumentState::Value{starbase_sbe::InstrumentState::NULL_VALUE}} == roq::TradingStatus::UNDEFINED);

template <>
template <>
std::optional<TradingStatus> Map<starbase_sbe::InstrumentState::Value>::helper() const {
  return Helper{args_};
}

// starbase_sbe::Liquidation::Value => roq::Liquidity

template <>
template <>
constexpr Helper<starbase_sbe::Liquidation::Value>::operator std::optional<Liquidity>() const {
  switch (std::get<0>(args_)) {
    using enum starbase_sbe::Liquidation::Value;
    case none:
      return Liquidity::UNDEFINED;
    case maker:
      return Liquidity::MAKER;
    case taker:
      return Liquidity::TAKER;
    case both:
      return Liquidity::UNDEFINED;  // ???
    case NULL_VALUE:
      return Liquidity::UNDEFINED;
  }
  return {};
}

static_assert(Helper{starbase_sbe::Liquidation::Value{starbase_sbe::Liquidation::none}} == roq::Liquidity::UNDEFINED);
static_assert(Helper{starbase_sbe::Liquidation::Value{starbase_sbe::Liquidation::maker}} == roq::Liquidity::MAKER);
static_assert(Helper{starbase_sbe::Liquidation::Value{starbase_sbe::Liquidation::taker}} == roq::Liquidity::TAKER);
static_assert(Helper{starbase_sbe::Liquidation::Value{starbase_sbe::Liquidation::both}} == roq::Liquidity::UNDEFINED);
static_assert(Helper{starbase_sbe::Liquidation::Value{starbase_sbe::Liquidation::NULL_VALUE}} == roq::Liquidity::UNDEFINED);

template <>
template <>
std::optional<Liquidity> Map<starbase_sbe::Liquidation::Value>::helper() const {
  return Helper{args_};
}

// starbase_sbe::YesNo::Value => std::bool

template <>
template <>
constexpr Helper<starbase_sbe::YesNo::Value>::operator std::optional<bool>() const {
  switch (std::get<0>(args_)) {
    using enum starbase_sbe::YesNo::Value;
    case no:
      return false;
    case yes:
      return true;
    case NULL_VALUE:
      return false;
  }
  return {};
}

static_assert(Helper{starbase_sbe::YesNo::Value{starbase_sbe::YesNo::no}} == false);
static_assert(Helper{starbase_sbe::YesNo::Value{starbase_sbe::YesNo::yes}} == true);
static_assert(Helper{starbase_sbe::YesNo::Value{starbase_sbe::YesNo::NULL_VALUE}} == false);

template <>
template <>
std::optional<bool> Map<starbase_sbe::YesNo::Value>::helper() const {
  return Helper{args_};
}

}  // namespace roq
