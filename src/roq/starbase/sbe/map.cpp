/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/sbe/map.hpp"

using namespace std::literals;

namespace roq {

namespace {
template <typename... Args>
using Helper = detail::MapHelper<Args...>;
}

// starbase => roq

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
      //
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

}  // namespace roq
