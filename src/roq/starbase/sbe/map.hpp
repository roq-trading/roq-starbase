/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <starbase_sbe/BookSide.h>
#include <starbase_sbe/Direction.h>
#include <starbase_sbe/InstrumentState.h>
#include <starbase_sbe/Liquidation.h>
#include <starbase_sbe/YesNo.h>

#include "roq/liquidity.hpp"
#include "roq/side.hpp"
#include "roq/trading_status.hpp"

#include "roq/map.hpp"

namespace roq {

template <>
template <>
std::optional<Side> Map<starbase_sbe::BookSide::Value>::helper() const;

template <>
template <>
std::optional<Side> Map<starbase_sbe::Direction::Value>::helper() const;

template <>
template <>
std::optional<TradingStatus> Map<starbase_sbe::InstrumentState::Value>::helper() const;

template <>
template <>
std::optional<Liquidity> Map<starbase_sbe::Liquidation::Value>::helper() const;

template <>
template <>
std::optional<bool> Map<starbase_sbe::YesNo::Value>::helper() const;

}  // namespace roq
