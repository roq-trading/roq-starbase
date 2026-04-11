/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <deribit_sbe_order/Bool.h>
#include <deribit_sbe_order/RejectReason.h>

#include "roq/error.hpp"

#include "roq/map.hpp"

namespace roq {

template <>
template <>
std::optional<bool> Map<deribit_sbe_order::Bool::Value>::helper() const;

template <>
template <>
std::optional<Error> Map<deribit_sbe_order::RejectReason::Value>::helper() const;

}  // namespace roq
