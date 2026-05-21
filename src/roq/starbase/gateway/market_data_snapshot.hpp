/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include "roq/utils/container.hpp"

#include "roq/utils/metrics/counter.hpp"
#include "roq/utils/metrics/profile.hpp"

#include "roq/io/context.hpp"

#include "roq/io/net/udp/receiver.hpp"

#include "roq/server.hpp"

#include "roq/starbase/gateway/channel.hpp"
#include "roq/starbase/gateway/shared.hpp"

#include "roq/starbase/sbe/parser_2.hpp"

namespace roq {
namespace starbase {
namespace gateway {

struct MarketDataSnapshot final : public io::net::udp::Receiver::Handler, public sbe::Parser2::Handler {
  struct Handler {
    virtual void operator()(Trace<StreamStatus> const &) = 0;
    virtual void operator()(Trace<ReferenceData> const &, bool is_last) = 0;
    virtual void operator()(Trace<MarketStatus> const &, bool is_last) = 0;
    virtual void operator()(Trace<MarketByOrderUpdate> const &, bool is_last) = 0;
    virtual void operator()(Trace<TradeSummary> const &, bool is_last) = 0;
    virtual void operator()(Trace<StatisticsUpdate> const &, bool is_last) = 0;
  };

  MarketDataSnapshot(Handler &, io::Context &, uint16_t stream_id, Shared &);

  MarketDataSnapshot(MarketDataSnapshot const &) = delete;

  void operator()(Event<Start> const &);
  void operator()(Event<Stop> const &);
  void operator()(Event<Timer> const &);

  void operator()(metrics::Writer &) const;

 protected:
  // io::net::udp::Receiver::Handler
  void operator()(io::net::udp::Receiver::Read const &) override;
  void operator()(io::net::udp::Receiver::Error const &) override;

  // sbe::Parser2::Handler
  bool operator()(sbe::PacketHeader const &) override;
  //
  void operator()(Trace<deribit::sbe::market_data::Instrument> const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &) override;
  void operator()(
      Trace<deribit::sbe::market_data::TradingStatusUpdate> const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &) override;
  void operator()(
      Trace<deribit::sbe::market_data::InstrumentInfo> const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &) override;
  void operator()(
      Trace<deribit::sbe::market_data::InstrumentRef> const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &) override;
  void operator()(Trace<deribit::sbe::market_data::BidPut> const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &) override;
  void operator()(Trace<deribit::sbe::market_data::AskPut> const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &) override;
  void operator()(
      Trace<deribit::sbe::market_data::BidQtyReduced> const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &) override;
  void operator()(
      Trace<deribit::sbe::market_data::AskQtyReduced> const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &) override;
  void operator()(Trace<deribit::sbe::market_data::BidDelete> const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &) override;
  void operator()(Trace<deribit::sbe::market_data::AskDelete> const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &) override;
  void operator()(
      Trace<deribit::sbe::market_data::TradeSummary> const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &) override;
  void operator()(Trace<deribit::sbe::market_data::Trade> const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &) override;
  void operator()(Trace<deribit::sbe::market_data::BlockTrade> const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &) override;
  void operator()(
      Trace<deribit::sbe::market_data::SnapshotHeader> const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &) override;
  void operator()(
      Trace<deribit::sbe::market_data::SnapshotTrailer> const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &) override;
  void operator()(Trace<deribit::sbe::market_data::EndOfCycle> const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &) override;
  void operator()(
      Trace<deribit::sbe::market_data::RetransmitRequest> const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &) override;
  void operator()(
      Trace<deribit::sbe::market_data::RetransmitReject> const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &) override;

  // utils

  void publish_stream_status(TraceInfo const &, ConnectionStatus, std::string_view const &reason = {});

  template <typename Callback>
  void get_channel(sbe::PacketHeader const &, Callback);

 private:
  Handler &handler_;
  // config
  uint16_t const stream_id_;
  std::string const name_;
  bool const publish_market_by_price_;
  Mask<SupportType> const supports_;
  // receiver
  std::unique_ptr<io::net::udp::Receiver> const receiver_;
  // metrics
  struct {
    utils::metrics::Counter disconnect;
  } counter_;
  struct {
    utils::metrics::Profile parse;
  } profile_;
  // cache
  Shared &shared_;
  ConnectionStatus connection_status_ = {};
  utils::unordered_map<uint16_t, Channel> channel_;
  // state
  std::chrono::nanoseconds last_update_time_ = {};
};

}  // namespace gateway
}  // namespace starbase
}  // namespace roq
