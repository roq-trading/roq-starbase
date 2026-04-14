/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <deribit/sbe/order/Bool.h>
#include <deribit/sbe/order/Decimal72.h>
#include <deribit/sbe/order/Price9.h>
#include <deribit/sbe/order/RejectReason.h>

#include <deribit/sbe/market_data/Price9.h>

#include <chrono>

#include "roq/error.hpp"

#include "roq/map.hpp"

namespace roq {

template <>
template <>
std::optional<std::chrono::nanoseconds> Map<int64_t, int64_t>::helper() const;

template <>
template <>
std::optional<double> Map<deribit::sbe::order::Decimal72>::helper() const;

template <>
template <>
std::optional<double> Map<deribit::sbe::order::Price9>::helper() const;

template <>
template <>
std::optional<bool> Map<deribit::sbe::order::Bool::Value>::helper() const;

template <>
template <>
std::optional<Error> Map<deribit::sbe::order::RejectReason::Value>::helper() const;

template <>
template <>
std::optional<double> Map<deribit::sbe::market_data::Price9>::helper() const;

}  // namespace roq
