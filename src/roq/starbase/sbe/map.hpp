/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <deribit_sbe_order/Decimal72.h>
#include <deribit_sbe_order/Price9.h>

#include <deribit_sbe_order/Bool.h>
#include <deribit_sbe_order/RejectReason.h>

#include <deribit_sbe_market_data/Price9.h>

#include "roq/error.hpp"

#include "roq/map.hpp"

namespace roq {

template <>
template <>
std::optional<double> Map<deribit_sbe_order::Decimal72>::helper() const;

template <>
template <>
std::optional<double> Map<deribit_sbe_order::Price9>::helper() const;

template <>
template <>
std::optional<bool> Map<deribit_sbe_order::Bool::Value>::helper() const;

template <>
template <>
std::optional<Error> Map<deribit_sbe_order::RejectReason::Value>::helper() const;

template <>
template <>
std::optional<double> Map<deribit_sbe_market_data::Price9>::helper() const;

}  // namespace roq
