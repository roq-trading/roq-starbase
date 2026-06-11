/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <span>

#include <deribit/sbe/order/MessageHeader.h>

#include <deribit/sbe/order/AmendOrderReject.h>
#include <deribit/sbe/order/AmendOrderRequest.h>
#include <deribit/sbe/order/AmendOrderResponse.h>
#include <deribit/sbe/order/CancelOrderReject.h>
#include <deribit/sbe/order/CancelOrderRequest.h>
#include <deribit/sbe/order/CancelOrderResponse.h>
#include <deribit/sbe/order/DummyMessage.h>
#include <deribit/sbe/order/GapFill.h>
#include <deribit/sbe/order/Heartbeat.h>
#include <deribit/sbe/order/LoggedOut.h>
#include <deribit/sbe/order/Logon.h>
#include <deribit/sbe/order/LogonConf.h>
#include <deribit/sbe/order/Logout.h>
#include <deribit/sbe/order/MassCancelReject.h>
#include <deribit/sbe/order/MassCancelRequest.h>
#include <deribit/sbe/order/MassCancelResponse.h>
#include <deribit/sbe/order/MassQuoteCancelRequest.h>
#include <deribit/sbe/order/MassQuoteMmpTriggered.h>
#include <deribit/sbe/order/MassQuoteMmpUnfrozen.h>
#include <deribit/sbe/order/MassQuoteOrdersPlaced.h>
#include <deribit/sbe/order/MassQuoteReject.h>
#include <deribit/sbe/order/MassQuoteRequest.h>
#include <deribit/sbe/order/MassQuoteResponse.h>
#include <deribit/sbe/order/NewOrderReject.h>
#include <deribit/sbe/order/NewOrderRequest.h>
#include <deribit/sbe/order/NewOrderResponse.h>
#include <deribit/sbe/order/OrderFilled.h>
#include <deribit/sbe/order/OrderPlaced.h>
#include <deribit/sbe/order/OrdersCanceled.h>
#include <deribit/sbe/order/OrdersMmpTriggered.h>
#include <deribit/sbe/order/OrdersMmpUnfrozen.h>
#include <deribit/sbe/order/Reject.h>
#include <deribit/sbe/order/ResendRequest.h>
#include <deribit/sbe/order/TestRequest.h>

#include "roq/trace.hpp"

namespace roq {
namespace starbase {
namespace protocol {
namespace sbe {

struct Parser final {
  struct Handler {
    virtual void operator()(Trace<deribit::sbe::order::Logon> const &, deribit::sbe::order::MessageHeader const &) = 0;                   // 1
    virtual void operator()(Trace<deribit::sbe::order::LogonConf> const &, deribit::sbe::order::MessageHeader const &) = 0;               // 2
    virtual void operator()(Trace<deribit::sbe::order::Logout> const &, deribit::sbe::order::MessageHeader const &) = 0;                  // 4
    virtual void operator()(Trace<deribit::sbe::order::LoggedOut> const &, deribit::sbe::order::MessageHeader const &) = 0;               // 5
    virtual void operator()(Trace<deribit::sbe::order::Heartbeat> const &, deribit::sbe::order::MessageHeader const &) = 0;               // 10
    virtual void operator()(Trace<deribit::sbe::order::TestRequest> const &, deribit::sbe::order::MessageHeader const &) = 0;             // 11
    virtual void operator()(Trace<deribit::sbe::order::ResendRequest> const &, deribit::sbe::order::MessageHeader const &) = 0;           // 20
    virtual void operator()(Trace<deribit::sbe::order::GapFill> const &, deribit::sbe::order::MessageHeader const &) = 0;                 // 21
    virtual void operator()(Trace<deribit::sbe::order::Reject> const &, deribit::sbe::order::MessageHeader const &) = 0;                  // 30
    virtual void operator()(Trace<deribit::sbe::order::NewOrderRequest> const &, deribit::sbe::order::MessageHeader const &) = 0;         // 100
    virtual void operator()(Trace<deribit::sbe::order::AmendOrderRequest> const &, deribit::sbe::order::MessageHeader const &) = 0;       // 110
    virtual void operator()(Trace<deribit::sbe::order::CancelOrderRequest> const &, deribit::sbe::order::MessageHeader const &) = 0;      // 120
    virtual void operator()(Trace<deribit::sbe::order::MassQuoteRequest> const &, deribit::sbe::order::MessageHeader const &) = 0;        // 130
    virtual void operator()(Trace<deribit::sbe::order::MassCancelRequest> const &, deribit::sbe::order::MessageHeader const &) = 0;       // 140
    virtual void operator()(Trace<deribit::sbe::order::MassQuoteCancelRequest> const &, deribit::sbe::order::MessageHeader const &) = 0;  // 145
    virtual void operator()(Trace<deribit::sbe::order::NewOrderResponse> const &, deribit::sbe::order::MessageHeader const &) = 0;        // 200
    virtual void operator()(Trace<deribit::sbe::order::NewOrderReject> const &, deribit::sbe::order::MessageHeader const &) = 0;          // 202
    virtual void operator()(Trace<deribit::sbe::order::AmendOrderResponse> const &, deribit::sbe::order::MessageHeader const &) = 0;      // 210
    virtual void operator()(Trace<deribit::sbe::order::AmendOrderReject> const &, deribit::sbe::order::MessageHeader const &) = 0;        // 212
    virtual void operator()(Trace<deribit::sbe::order::CancelOrderResponse> const &, deribit::sbe::order::MessageHeader const &) = 0;     // 220
    virtual void operator()(Trace<deribit::sbe::order::CancelOrderReject> const &, deribit::sbe::order::MessageHeader const &) = 0;       // 222
    virtual void operator()(Trace<deribit::sbe::order::MassQuoteResponse> const &, deribit::sbe::order::MessageHeader const &) = 0;       // 230
    virtual void operator()(Trace<deribit::sbe::order::MassQuoteReject> const &, deribit::sbe::order::MessageHeader const &) = 0;         // 232
    virtual void operator()(Trace<deribit::sbe::order::MassCancelResponse> const &, deribit::sbe::order::MessageHeader const &) = 0;      // 240
    virtual void operator()(Trace<deribit::sbe::order::MassCancelReject> const &, deribit::sbe::order::MessageHeader const &) = 0;        // 242
    virtual void operator()(Trace<deribit::sbe::order::OrderFilled> const &, deribit::sbe::order::MessageHeader const &) = 0;             // 300
    virtual void operator()(Trace<deribit::sbe::order::OrdersCanceled> const &, deribit::sbe::order::MessageHeader const &) = 0;          // 310
    virtual void operator()(Trace<deribit::sbe::order::OrderPlaced> const &, deribit::sbe::order::MessageHeader const &) = 0;             // 312
    virtual void operator()(Trace<deribit::sbe::order::MassQuoteOrdersPlaced> const &, deribit::sbe::order::MessageHeader const &) = 0;   // 314
    virtual void operator()(Trace<deribit::sbe::order::MassQuoteMmpTriggered> const &, deribit::sbe::order::MessageHeader const &) = 0;   // 320
    virtual void operator()(Trace<deribit::sbe::order::OrdersMmpTriggered> const &, deribit::sbe::order::MessageHeader const &) = 0;      // 322
    virtual void operator()(Trace<deribit::sbe::order::MassQuoteMmpUnfrozen> const &, deribit::sbe::order::MessageHeader const &) = 0;    // 324
    virtual void operator()(Trace<deribit::sbe::order::OrdersMmpUnfrozen> const &, deribit::sbe::order::MessageHeader const &) = 0;       // 326
    virtual void operator()(Trace<deribit::sbe::order::DummyMessage> const &, deribit::sbe::order::MessageHeader const &) = 0;            // 9999
  };

  static bool dispatch(Handler &, std::span<std::byte const> const &buffer, TraceInfo const &);
};

}  // namespace sbe
}  // namespace protocol
}  // namespace starbase
}  // namespace roq
