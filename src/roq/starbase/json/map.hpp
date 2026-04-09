/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include "roq/starbase/json/direction.hpp"
#include "roq/starbase/json/liquidity.hpp"
#include "roq/starbase/json/state.hpp"

#include "roq/liquidity.hpp"
#include "roq/side.hpp"
#include "roq/trading_status.hpp"

#include "roq/map.hpp"

namespace roq {

template <>
template <>
std::optional<Side> Map<starbase::json::Direction>::helper() const;

template <>
template <>
std::optional<Liquidity> Map<starbase::json::Liquidity>::helper() const;

template <>
template <>
std::optional<TradingStatus> Map<starbase::json::State>::helper() const;

}  // namespace roq
