/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <span>

#include <starbase_sbe/Book.h>           // 1001
#include <starbase_sbe/ComboLegs.h>      // 1007
#include <starbase_sbe/Instrument.h>     // 1000
#include <starbase_sbe/InstrumentV2.h>   // 1010
#include <starbase_sbe/PriceIndex.h>     // 1008
#include <starbase_sbe/Rfq.h>            // 1009
#include <starbase_sbe/Snapshot.h>       // 1004
#include <starbase_sbe/SnapshotEnd.h>    // 1006
#include <starbase_sbe/SnapshotStart.h>  // 1005
#include <starbase_sbe/Ticker.h>         // 1003
#include <starbase_sbe/Trades.h>         // 1002

#include "roq/trace.hpp"

#include "roq/starbase/sbe/frame.hpp"

namespace roq {
namespace starbase {
namespace sbe {

struct Parser final {
  struct Handler {
    virtual bool operator()(Frame const &) = 0;

    virtual void operator()(Trace<starbase_sbe::Instrument> const &, Frame const &) = 0;     // 1000
    virtual void operator()(Trace<starbase_sbe::Book> const &, Frame const &) = 0;           // 1001
    virtual void operator()(Trace<starbase_sbe::Trades> const &, Frame const &) = 0;         // 1002
    virtual void operator()(Trace<starbase_sbe::Ticker> const &, Frame const &) = 0;         // 1003
    virtual void operator()(Trace<starbase_sbe::Snapshot> const &, Frame const &) = 0;       // 1004
    virtual void operator()(Trace<starbase_sbe::SnapshotStart> const &, Frame const &) = 0;  // 1005
    virtual void operator()(Trace<starbase_sbe::SnapshotEnd> const &, Frame const &) = 0;    // 1006
    virtual void operator()(Trace<starbase_sbe::ComboLegs> const &, Frame const &) = 0;      // 1007
    virtual void operator()(Trace<starbase_sbe::PriceIndex> const &, Frame const &) = 0;     // 1008
    virtual void operator()(Trace<starbase_sbe::Rfq> const &, Frame const &) = 0;            // 1009
    virtual void operator()(Trace<starbase_sbe::InstrumentV2> const &, Frame const &) = 0;   // 1010
  };

  static bool dispatch(Handler &, std::span<std::byte const> const &buffer, TraceInfo const &);
};

}  // namespace sbe
}  // namespace starbase
}  // namespace roq
