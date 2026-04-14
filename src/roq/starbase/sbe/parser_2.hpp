/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <span>

// incremental
#include <deribit/sbe/market_data/AskDelete.h>
#include <deribit/sbe/market_data/AskPut.h>
#include <deribit/sbe/market_data/AskQtyReduced.h>
#include <deribit/sbe/market_data/BidDelete.h>
#include <deribit/sbe/market_data/BidPut.h>
#include <deribit/sbe/market_data/BidQtyReduced.h>
#include <deribit/sbe/market_data/BlockTrade.h>
#include <deribit/sbe/market_data/Instrument.h>
#include <deribit/sbe/market_data/InstrumentInfo.h>
#include <deribit/sbe/market_data/InstrumentRef.h>
#include <deribit/sbe/market_data/Trade.h>
#include <deribit/sbe/market_data/TradeSummary.h>
#include <deribit/sbe/market_data/TradingStatusUpdate.h>

// snapshot
#include <deribit/sbe/market_data/EndOfCycle.h>
#include <deribit/sbe/market_data/SnapshotHeader.h>
#include <deribit/sbe/market_data/SnapshotTrailer.h>

// retransmit
#include <deribit/sbe/market_data/RetransmitReject.h>
#include <deribit/sbe/market_data/RetransmitRequest.h>

#include "roq/trace.hpp"

#include "roq/starbase/sbe/packet_header.hpp"

namespace roq {
namespace starbase {
namespace sbe {

struct Parser2 final {
  struct Handler {
    virtual bool operator()(PacketHeader const &) = 0;

    virtual void operator()(
        Trace<deribit::sbe::market_data::Instrument> const &, deribit::sbe::market_data::MdMessageHeader const &, PacketHeader const &) = 0;  // 10
    virtual void operator()(
        Trace<deribit::sbe::market_data::TradingStatusUpdate> const &, deribit::sbe::market_data::MdMessageHeader const &, PacketHeader const &) = 0;  // 12
    virtual void operator()(
        Trace<deribit::sbe::market_data::InstrumentInfo> const &, deribit::sbe::market_data::MdMessageHeader const &, PacketHeader const &) = 0;  // 13
    virtual void operator()(
        Trace<deribit::sbe::market_data::InstrumentRef> const &, deribit::sbe::market_data::MdMessageHeader const &, PacketHeader const &) = 0;  // 14
    virtual void operator()(
        Trace<deribit::sbe::market_data::BidPut> const &, deribit::sbe::market_data::MdMessageHeader const &, PacketHeader const &) = 0;  // 20
    virtual void operator()(
        Trace<deribit::sbe::market_data::AskPut> const &, deribit::sbe::market_data::MdMessageHeader const &, PacketHeader const &) = 0;  // 21
    virtual void operator()(
        Trace<deribit::sbe::market_data::BidQtyReduced> const &, deribit::sbe::market_data::MdMessageHeader const &, PacketHeader const &) = 0;  // 22
    virtual void operator()(
        Trace<deribit::sbe::market_data::AskQtyReduced> const &, deribit::sbe::market_data::MdMessageHeader const &, PacketHeader const &) = 0;  // 23
    virtual void operator()(
        Trace<deribit::sbe::market_data::BidDelete> const &, deribit::sbe::market_data::MdMessageHeader const &, PacketHeader const &) = 0;  // 24
    virtual void operator()(
        Trace<deribit::sbe::market_data::AskDelete> const &, deribit::sbe::market_data::MdMessageHeader const &, PacketHeader const &) = 0;  // 25
    virtual void operator()(
        Trace<deribit::sbe::market_data::TradeSummary> const &, deribit::sbe::market_data::MdMessageHeader const &, PacketHeader const &) = 0;  // 30
    virtual void operator()(
        Trace<deribit::sbe::market_data::Trade> const &, deribit::sbe::market_data::MdMessageHeader const &, PacketHeader const &) = 0;  // 31
    virtual void operator()(
        Trace<deribit::sbe::market_data::BlockTrade> const &, deribit::sbe::market_data::MdMessageHeader const &, PacketHeader const &) = 0;  // 33
    virtual void operator()(
        Trace<deribit::sbe::market_data::SnapshotHeader> const &, deribit::sbe::market_data::MdMessageHeader const &, PacketHeader const &) = 0;  // 100
    virtual void operator()(
        Trace<deribit::sbe::market_data::SnapshotTrailer> const &, deribit::sbe::market_data::MdMessageHeader const &, PacketHeader const &) = 0;  // 101
    virtual void operator()(
        Trace<deribit::sbe::market_data::EndOfCycle> const &, deribit::sbe::market_data::MdMessageHeader const &, PacketHeader const &) = 0;  // 119
    virtual void operator()(
        Trace<deribit::sbe::market_data::RetransmitRequest> const &, deribit::sbe::market_data::MdMessageHeader const &, PacketHeader const &) = 0;  // 200
    virtual void operator()(
        Trace<deribit::sbe::market_data::RetransmitReject> const &, deribit::sbe::market_data::MdMessageHeader const &, PacketHeader const &) = 0;  // 202
  };

  static bool dispatch(Handler &, std::span<std::byte const> const &buffer, TraceInfo const &);
};

}  // namespace sbe
}  // namespace starbase
}  // namespace roq
