/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <span>

#include <deribit_sbe_order/AmendOrderReject.h>
#include <deribit_sbe_order/AmendOrderRequest.h>
#include <deribit_sbe_order/AmendOrderResponse.h>
#include <deribit_sbe_order/CancelOrderReject.h>
#include <deribit_sbe_order/CancelOrderRequest.h>
#include <deribit_sbe_order/CancelOrderResponse.h>
#include <deribit_sbe_order/DummyMessage.h>
#include <deribit_sbe_order/GapFill.h>
#include <deribit_sbe_order/Heartbeat.h>
#include <deribit_sbe_order/LoggedOut.h>
#include <deribit_sbe_order/Logon.h>
#include <deribit_sbe_order/LogonConf.h>
#include <deribit_sbe_order/Logout.h>
#include <deribit_sbe_order/MassCancelReject.h>
#include <deribit_sbe_order/MassCancelRequest.h>
#include <deribit_sbe_order/MassCancelResponse.h>
#include <deribit_sbe_order/MassQuoteCancelRequest.h>
#include <deribit_sbe_order/MassQuoteMmpTriggered.h>
#include <deribit_sbe_order/MassQuoteMmpUnfrozen.h>
#include <deribit_sbe_order/MassQuoteOrdersPlaced.h>
#include <deribit_sbe_order/MassQuoteReject.h>
#include <deribit_sbe_order/MassQuoteRequest.h>
#include <deribit_sbe_order/MassQuoteResponse.h>
#include <deribit_sbe_order/NewOrderReject.h>
#include <deribit_sbe_order/NewOrderRequest.h>
#include <deribit_sbe_order/NewOrderResponse.h>
#include <deribit_sbe_order/OrderFilled.h>
#include <deribit_sbe_order/OrderPlaced.h>
#include <deribit_sbe_order/OrdersCanceled.h>
#include <deribit_sbe_order/OrdersMmpTriggered.h>
#include <deribit_sbe_order/OrdersMmpUnfrozen.h>
#include <deribit_sbe_order/Reject.h>
#include <deribit_sbe_order/ResendRequest.h>
#include <deribit_sbe_order/TestRequest.h>

#include "roq/trace.hpp"

#include "roq/starbase/sbe/frame.hpp"

namespace roq {
namespace starbase {
namespace sbe {

struct Parser final {
  struct Handler {
    virtual bool operator()(Frame const &) = 0;

    virtual void operator()(Trace<deribit_sbe_order::Logon> const &, Frame const &) = 0;                   // 1
    virtual void operator()(Trace<deribit_sbe_order::LogonConf> const &, Frame const &) = 0;               // 2
    virtual void operator()(Trace<deribit_sbe_order::Logout> const &, Frame const &) = 0;                  // 4
    virtual void operator()(Trace<deribit_sbe_order::LoggedOut> const &, Frame const &) = 0;               // 5
    virtual void operator()(Trace<deribit_sbe_order::Heartbeat> const &, Frame const &) = 0;               // 10
    virtual void operator()(Trace<deribit_sbe_order::TestRequest> const &, Frame const &) = 0;             // 11
    virtual void operator()(Trace<deribit_sbe_order::ResendRequest> const &, Frame const &) = 0;           // 20
    virtual void operator()(Trace<deribit_sbe_order::GapFill> const &, Frame const &) = 0;                 // 21
    virtual void operator()(Trace<deribit_sbe_order::Reject> const &, Frame const &) = 0;                  // 30
    virtual void operator()(Trace<deribit_sbe_order::NewOrderRequest> const &, Frame const &) = 0;         // 100
    virtual void operator()(Trace<deribit_sbe_order::AmendOrderRequest> const &, Frame const &) = 0;       // 110
    virtual void operator()(Trace<deribit_sbe_order::CancelOrderRequest> const &, Frame const &) = 0;      // 120
    virtual void operator()(Trace<deribit_sbe_order::MassQuoteRequest> const &, Frame const &) = 0;        // 130
    virtual void operator()(Trace<deribit_sbe_order::MassCancelRequest> const &, Frame const &) = 0;       // 140
    virtual void operator()(Trace<deribit_sbe_order::MassQuoteCancelRequest> const &, Frame const &) = 0;  // 145
    virtual void operator()(Trace<deribit_sbe_order::NewOrderResponse> const &, Frame const &) = 0;        // 200
    virtual void operator()(Trace<deribit_sbe_order::NewOrderReject> const &, Frame const &) = 0;          // 202
    virtual void operator()(Trace<deribit_sbe_order::AmendOrderResponse> const &, Frame const &) = 0;      // 210
    virtual void operator()(Trace<deribit_sbe_order::AmendOrderReject> const &, Frame const &) = 0;        // 212
    virtual void operator()(Trace<deribit_sbe_order::CancelOrderResponse> const &, Frame const &) = 0;     // 220
    virtual void operator()(Trace<deribit_sbe_order::CancelOrderReject> const &, Frame const &) = 0;       // 220
    virtual void operator()(Trace<deribit_sbe_order::MassQuoteResponse> const &, Frame const &) = 0;       // 230
    virtual void operator()(Trace<deribit_sbe_order::MassQuoteReject> const &, Frame const &) = 0;         // 232
    virtual void operator()(Trace<deribit_sbe_order::MassCancelResponse> const &, Frame const &) = 0;      // 240
    virtual void operator()(Trace<deribit_sbe_order::MassCancelReject> const &, Frame const &) = 0;        // 242
    virtual void operator()(Trace<deribit_sbe_order::OrderFilled> const &, Frame const &) = 0;             // 300
    virtual void operator()(Trace<deribit_sbe_order::OrdersCanceled> const &, Frame const &) = 0;          // 310
    virtual void operator()(Trace<deribit_sbe_order::OrderPlaced> const &, Frame const &) = 0;             // 312
    virtual void operator()(Trace<deribit_sbe_order::MassQuoteOrdersPlaced> const &, Frame const &) = 0;   // 314
    virtual void operator()(Trace<deribit_sbe_order::MassQuoteMmpTriggered> const &, Frame const &) = 0;   // 320
    virtual void operator()(Trace<deribit_sbe_order::OrdersMmpTriggered> const &, Frame const &) = 0;      // 322
    virtual void operator()(Trace<deribit_sbe_order::MassQuoteMmpUnfrozen> const &, Frame const &) = 0;    // 324
    virtual void operator()(Trace<deribit_sbe_order::OrdersMmpUnfrozen> const &, Frame const &) = 0;       // 326
    virtual void operator()(Trace<deribit_sbe_order::DummyMessage> const &, Frame const &) = 0;            // 9999
  };

  static bool dispatch(Handler &, std::span<std::byte const> const &buffer, TraceInfo const &);
};

}  // namespace sbe
}  // namespace starbase
}  // namespace roq
