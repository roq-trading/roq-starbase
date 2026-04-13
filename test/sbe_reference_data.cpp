/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include <catch2/catch_all.hpp>

#include <fmt/format.h>

#include <cmath>
#include <span>

#include "roq/starbase/sbe/parser_2.hpp"

using namespace std::literals;

using namespace Catch::literals;

using namespace roq;
using namespace roq::starbase;

TEST_CASE("simple", "[sbe_reference_data]") {
  auto message =
      /*
        "\x01\x00\x5e\x00\x0c\xe9\x00\x0f"
        "\x53\xca\x49\xe0\x08\x00\x45\x00"
        "\x00\x64\x25\xbc"
        "\x40\x00"
        "\x10\x11"
        "\x6e\xd0\xc3\x8a\x25\x89\xe0\x00"
        "\x0c\xe9\xe7\xc2\x10\x7c\x00\x50\xd6\x5e"
        //
        */
      "\x9d\xad\x06\xc4\x0c\x14\xa5\x18"  // sending_time
      "\xa5\x58\x00\x00\x00\x00\x00\x00"  // seq_num
      "\x35\xaf\x00\x00"                  // channel_id=44853
      "\x01\x00"                          // type=snapshot(1)
      "\x01\x00"                          // message_count=1
      //
      "\x30\x00"                          // message_length=48
      "\x15\x00"                          // template_id=AskPut(21)
      "\x00\x00"                          // version=0
      "\x03\x00"                          // flags=???
      "\x97\x01\x06\xc4\x0c\x14\xa5\x18"  // transact_time
      //
      "\x00\x00\x80\xa2\xc1\x5f\x56\x02"     // order_id
      "\xf9\xd9\x04\x00\x00\x00\x00\x00"     // instrument_id
      "\x0a\x00\x00\x00\x00\x00\x00\x00"     // quantity_mantissa
      "\x00\x0f\x26\x40\x54\x04\x00\x00"sv;  // price
  // static_assert(std::size(message) == 132);
  struct MyHandler final : public sbe::Parser2::Handler {
    int counter = 0;
    bool operator()(sbe::Frame const &) { return true; }
    //
    void operator()(Trace<deribit_sbe_market_data::Instrument> const &, sbe::Frame const &) override { FAIL(); }
    void operator()(Trace<deribit_sbe_market_data::TradingStatusUpdate> const &, sbe::Frame const &) override { FAIL(); }
    void operator()(Trace<deribit_sbe_market_data::InstrumentInfo> const &, sbe::Frame const &) override { FAIL(); }
    void operator()(Trace<deribit_sbe_market_data::InstrumentRef> const &, sbe::Frame const &) override { FAIL(); }
    void operator()(Trace<deribit_sbe_market_data::BidPut> const &, sbe::Frame const &) override { FAIL(); }
    void operator()(Trace<deribit_sbe_market_data::AskPut> const &, sbe::Frame const &) override { FAIL(); }
    void operator()(Trace<deribit_sbe_market_data::BidQtyReduced> const &, sbe::Frame const &) override { FAIL(); }
    void operator()(Trace<deribit_sbe_market_data::AskQtyReduced> const &, sbe::Frame const &) override { FAIL(); }
    void operator()(Trace<deribit_sbe_market_data::BidDelete> const &, sbe::Frame const &) override { FAIL(); }
    void operator()(Trace<deribit_sbe_market_data::AskDelete> const &, sbe::Frame const &) override { FAIL(); }
    void operator()(Trace<deribit_sbe_market_data::TradeSummary> const &, sbe::Frame const &) override { FAIL(); }
    void operator()(Trace<deribit_sbe_market_data::Trade> const &, sbe::Frame const &) override { FAIL(); }
    void operator()(Trace<deribit_sbe_market_data::BlockTrade> const &, sbe::Frame const &) override { FAIL(); }
    void operator()(Trace<deribit_sbe_market_data::SnapshotHeader> const &, sbe::Frame const &) override { FAIL(); }
    void operator()(Trace<deribit_sbe_market_data::SnapshotTrailer> const &, sbe::Frame const &) override { FAIL(); }
    void operator()(Trace<deribit_sbe_market_data::EndOfCycle> const &, sbe::Frame const &) override { FAIL(); }
    void operator()(Trace<deribit_sbe_market_data::RetransmitRequest> const &, sbe::Frame const &) override { FAIL(); }
    void operator()(Trace<deribit_sbe_market_data::RetransmitReject> const &, sbe::Frame const &) override { FAIL(); }
  } handler;
  std::span buffer{reinterpret_cast<std::byte const *>(std::data(message)), std::size(message)};
  TraceInfo trace_info;
  // auto res = sbe::Parser2::dispatch(handler, buffer, trace_info);
  // CHECK(res);
  // CHECK(handler.counter == 2);
}
