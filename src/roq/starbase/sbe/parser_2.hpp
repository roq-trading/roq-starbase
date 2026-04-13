/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <span>

// incremental
#include <deribit_sbe_market_data/AskDelete.h>
#include <deribit_sbe_market_data/AskPut.h>
#include <deribit_sbe_market_data/AskQtyReduced.h>
#include <deribit_sbe_market_data/BidDelete.h>
#include <deribit_sbe_market_data/BidPut.h>
#include <deribit_sbe_market_data/BidQtyReduced.h>
#include <deribit_sbe_market_data/BlockTrade.h>
#include <deribit_sbe_market_data/Instrument.h>
#include <deribit_sbe_market_data/InstrumentInfo.h>
#include <deribit_sbe_market_data/InstrumentRef.h>
#include <deribit_sbe_market_data/Trade.h>
#include <deribit_sbe_market_data/TradeSummary.h>
#include <deribit_sbe_market_data/TradingStatusUpdate.h>

// snapshot
#include <deribit_sbe_market_data/EndOfCycle.h>
#include <deribit_sbe_market_data/SnapshotHeader.h>
#include <deribit_sbe_market_data/SnapshotTrailer.h>

// retransmit
#include <deribit_sbe_market_data/RetransmitReject.h>
#include <deribit_sbe_market_data/RetransmitRequest.h>

#include "roq/trace.hpp"

#include "roq/starbase/sbe/frame.hpp"

namespace roq {
namespace starbase {
namespace sbe {

struct Parser2 final {
  struct Handler {
    virtual bool operator()(Frame const &) = 0;

    virtual void operator()(Trace<deribit_sbe_market_data::Instrument> const &, deribit_sbe_market_data::MdMessageHeader const &, Frame const &) = 0;  // 10
    virtual void operator()(
        Trace<deribit_sbe_market_data::TradingStatusUpdate> const &, deribit_sbe_market_data::MdMessageHeader const &, Frame const &) = 0;                 // 12
    virtual void operator()(Trace<deribit_sbe_market_data::InstrumentInfo> const &, deribit_sbe_market_data::MdMessageHeader const &, Frame const &) = 0;  // 13
    virtual void operator()(Trace<deribit_sbe_market_data::InstrumentRef> const &, deribit_sbe_market_data::MdMessageHeader const &, Frame const &) = 0;   // 14
    virtual void operator()(Trace<deribit_sbe_market_data::BidPut> const &, deribit_sbe_market_data::MdMessageHeader const &, Frame const &) = 0;          // 20
    virtual void operator()(Trace<deribit_sbe_market_data::AskPut> const &, deribit_sbe_market_data::MdMessageHeader const &, Frame const &) = 0;          // 21
    virtual void operator()(Trace<deribit_sbe_market_data::BidQtyReduced> const &, deribit_sbe_market_data::MdMessageHeader const &, Frame const &) = 0;   // 22
    virtual void operator()(Trace<deribit_sbe_market_data::AskQtyReduced> const &, deribit_sbe_market_data::MdMessageHeader const &, Frame const &) = 0;   // 23
    virtual void operator()(Trace<deribit_sbe_market_data::BidDelete> const &, deribit_sbe_market_data::MdMessageHeader const &, Frame const &) = 0;       // 24
    virtual void operator()(Trace<deribit_sbe_market_data::AskDelete> const &, deribit_sbe_market_data::MdMessageHeader const &, Frame const &) = 0;       // 25
    virtual void operator()(Trace<deribit_sbe_market_data::TradeSummary> const &, deribit_sbe_market_data::MdMessageHeader const &, Frame const &) = 0;    // 30
    virtual void operator()(Trace<deribit_sbe_market_data::Trade> const &, deribit_sbe_market_data::MdMessageHeader const &, Frame const &) = 0;           // 31
    virtual void operator()(Trace<deribit_sbe_market_data::BlockTrade> const &, deribit_sbe_market_data::MdMessageHeader const &, Frame const &) = 0;      // 33
    virtual void operator()(
        Trace<deribit_sbe_market_data::SnapshotHeader> const &, deribit_sbe_market_data::MdMessageHeader const &, Frame const &) = 0;  // 100
    virtual void operator()(
        Trace<deribit_sbe_market_data::SnapshotTrailer> const &, deribit_sbe_market_data::MdMessageHeader const &, Frame const &) = 0;                 // 101
    virtual void operator()(Trace<deribit_sbe_market_data::EndOfCycle> const &, deribit_sbe_market_data::MdMessageHeader const &, Frame const &) = 0;  // 119
    virtual void operator()(
        Trace<deribit_sbe_market_data::RetransmitRequest> const &, deribit_sbe_market_data::MdMessageHeader const &, Frame const &) = 0;  // 200
    virtual void operator()(
        Trace<deribit_sbe_market_data::RetransmitReject> const &, deribit_sbe_market_data::MdMessageHeader const &, Frame const &) = 0;  // 202
  };

  static bool dispatch(Handler &, std::span<std::byte const> const &buffer, TraceInfo const &);
};

}  // namespace sbe
}  // namespace starbase
}  // namespace roq
