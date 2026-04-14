/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/sbe/map.hpp"

#include <cmath>
#include <limits>

using namespace std::literals;

namespace roq {

namespace {
template <typename... Args>
using Helper = detail::MapHelper<Args...>;
}

// deribit_sbe_order => std

// deribit_sbe_order::int64_t => std::chrono::nanoseconds

template <>
template <>
constexpr Helper<int64_t, int64_t>::operator std::optional<std::chrono::nanoseconds>() const {
  auto &value = std::get<0>(args_);
  auto &null_value = std::get<1>(args_);
  if (value == null_value) {
    return std::chrono::nanoseconds{};
  }
  return std::chrono::nanoseconds{value};
}

// static_assert(Helper{deribit_sbe_order::Bool::Value{deribit_sbe_order::Bool::FALSE}} == false);

template <>
template <>
std::optional<std::chrono::nanoseconds> Map<int64_t, int64_t>::helper() const {
  return Helper{args_};
}

// deribit_sbe_order => roq

// deribit_sbe_order::Decimal72 => double

template <>
template <>
constexpr Helper<deribit_sbe_order::Decimal72>::operator std::optional<double>() const {
  auto &value = std::get<0>(args_);
  auto mantissa = value.mantissa();
  auto exponent = value.exponent();
  if (mantissa == value.mantissaNullValue() || exponent == value.exponentNullValue()) {
    return std::numeric_limits<double>::quiet_NaN();
  }
  return static_cast<double>(mantissa) * std::pow(10.0, exponent);
}

// static_assert(Helper{deribit_sbe_order::Bool::Value{deribit_sbe_order::Bool::FALSE}} == false);

template <>
template <>
std::optional<double> Map<deribit_sbe_order::Decimal72>::helper() const {
  return Helper{args_};
}

// deribit_sbe_order::Price9 => double

template <>
template <>
constexpr Helper<deribit_sbe_order::Price9>::operator std::optional<double>() const {
  auto &value = std::get<0>(args_);
  auto price9 = value.price9();
  auto exponent = value.exponent();
  if (price9 == value.price9NullValue() || exponent == value.exponentNullValue()) {
    return std::numeric_limits<double>::quiet_NaN();
  }
  return static_cast<double>(price9) * std::pow(10.0, exponent);
}

// static_assert(Helper{deribit_sbe_order::Bool::Value{deribit_sbe_order::Bool::FALSE}} == false);

template <>
template <>
std::optional<double> Map<deribit_sbe_order::Price9>::helper() const {
  return Helper{args_};
}

// deribit_sbe_order::Bool::Value => bool

template <>
template <>
constexpr Helper<deribit_sbe_order::Bool::Value>::operator std::optional<bool>() const {
  switch (std::get<0>(args_)) {
    using enum deribit_sbe_order::Bool::Value;
    case FALSE:
      return false;
    case TRUE:
      return true;
    case NULL_VALUE:
      return false;
  }
  return {};
}

static_assert(Helper{deribit_sbe_order::Bool::Value{deribit_sbe_order::Bool::FALSE}} == false);
static_assert(Helper{deribit_sbe_order::Bool::Value{deribit_sbe_order::Bool::TRUE}} == true);
static_assert(Helper{deribit_sbe_order::Bool::Value{deribit_sbe_order::Bool::NULL_VALUE}} == false);

template <>
template <>
std::optional<bool> Map<deribit_sbe_order::Bool::Value>::helper() const {
  return Helper{args_};
}

// deribit_sbe_order::RejectReason::Value => roq::Error

template <>
template <>
constexpr Helper<deribit_sbe_order::RejectReason::Value>::operator std::optional<Error>() const {
  switch (std::get<0>(args_)) {
    using enum deribit_sbe_order::RejectReason::Value;
    case INVALID_SCHEMA_ID:
      return Error::UNDEFINED;
    case INVALID_TEMPLATE_ID:
      return Error::UNDEFINED;
    case INVALID_BLOCK_LENGTH:
      return Error::UNDEFINED;
    case INVALID_FIELD_VALUE:
      return Error::UNDEFINED;
    case NULL_VALUE:
      return Error::UNDEFINED;
  }
  return {};
}

static_assert(Helper{deribit_sbe_order::RejectReason::Value{deribit_sbe_order::RejectReason::INVALID_SCHEMA_ID}} == roq::Error::UNDEFINED);
//
static_assert(Helper{deribit_sbe_order::RejectReason::Value{deribit_sbe_order::RejectReason::NULL_VALUE}} == roq::Error::UNDEFINED);

template <>
template <>
std::optional<Error> Map<deribit_sbe_order::RejectReason::Value>::helper() const {
  return Helper{args_};
}

// deribit_sbe_market_data::Price9 => double

template <>
template <>
constexpr Helper<deribit_sbe_market_data::Price9>::operator std::optional<double>() const {
  auto &value = std::get<0>(args_);
  auto price9 = value.price9();
  auto exponent = value.exponent();
  if (price9 == value.price9NullValue() || exponent == value.exponentNullValue()) {
    return std::numeric_limits<double>::quiet_NaN();
  }
  return static_cast<double>(price9) * std::pow(10.0, exponent);
}

// static_assert(Helper{deribit_sbe_market_data::Bool::Value{deribit_sbe_market_data::Bool::FALSE}} == false);

template <>
template <>
std::optional<double> Map<deribit_sbe_market_data::Price9>::helper() const {
  return Helper{args_};
}

}  // namespace roq
