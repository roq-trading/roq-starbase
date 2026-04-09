/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <string_view>

#include "roq/trace_info.hpp"

#include "roq/core/json/buffer_stack.hpp"

#include "roq/starbase/json/auth.hpp"

#include "roq/starbase/json/subscribe_ack.hpp"

#include "roq/starbase/json/chart_trades.hpp"
#include "roq/starbase/json/instrument_state.hpp"
#include "roq/starbase/json/platform_state.hpp"
#include "roq/starbase/json/quote.hpp"
#include "roq/starbase/json/ticker.hpp"

#include "roq/starbase/json/user_changes.hpp"
#include "roq/starbase/json/user_orders.hpp"
#include "roq/starbase/json/user_portfolio.hpp"
#include "roq/starbase/json/user_trades.hpp"

#include "roq/starbase/json/get_account_summary_ack.hpp"
#include "roq/starbase/json/get_user_trades_by_currency_ack.hpp"

namespace roq {
namespace starbase {
namespace json {

struct Parser final {
  struct Handler {
    virtual void operator()(Trace<Auth> const &) = 0;
    virtual void operator()(Trace<SubscribeAck> const &) = 0;
    // public
    virtual void operator()(Trace<PlatformState> const &) = 0;
    virtual void operator()(Trace<InstrumentState> const &) = 0;
    virtual void operator()(Trace<Quote> const &) = 0;
    virtual void operator()(Trace<Ticker> const &) = 0;
    virtual void operator()(Trace<ChartTrades> const &, std::string_view const &symbol, uint32_t interval) = 0;
    // private
    virtual void operator()(Trace<UserPortfolio> const &) = 0;
    virtual void operator()(Trace<UserChanges> const &) = 0;
    virtual void operator()(Trace<UserOrders> const &) = 0;
    virtual void operator()(Trace<UserTrades> const &) = 0;
    //
    virtual void operator()(Trace<GetAccountSummaryAck> const &) = 0;
    virtual void operator()(Trace<GetUserTradesByCurrencyAck> const &) = 0;
  };

  static bool dispatch(Handler &, std::string_view const &message, core::json::BufferStack &, TraceInfo const &, bool allow_unknown_event_types);
};

}  // namespace json
}  // namespace starbase
}  // namespace roq
