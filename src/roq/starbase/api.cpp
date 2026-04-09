/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/api.hpp"

using namespace std::literals;

namespace roq {
namespace starbase {

// === IMPLEMENTATION ===

API API::create(Settings const &) {
  return {
      .market_data{
          .currencies = "/api/v2/public/get_currencies"sv,
          .instruments = "/api/v2/public/get_instruments"sv,
          .chart_data = "/api/v2/public/get_tradingview_chart_data"sv,
      },
      .order_management{},
  };
}

}  // namespace starbase
}  // namespace roq
