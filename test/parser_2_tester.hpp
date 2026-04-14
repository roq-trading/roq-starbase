/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include <catch2/catch_all.hpp>

#include "roq/starbase/sbe/parser_2.hpp"

namespace roq {
namespace starbase {

template <typename T>
struct Parser2Tester final : public sbe::Parser2::Handler {
  using value_type = std::remove_cvref_t<T>;
  using callback_type = std::function<void(value_type const &, deribit::sbe::market_data::MdMessageHeader const &, sbe::PacketHeader const &)>;

  static void dispatch(callback_type const &callback, auto const &message) {
    // XXX FIXME TODO catch2 block ???
    Parser2Tester handler{callback};
    auto res = sbe::Parser2::dispatch(handler, std::span{reinterpret_cast<std::byte const *>(std::data(message)), std::size(message)}, {});
    CHECK(res == true);
    CHECK(handler.found_ == true);
  }

 protected:
  explicit Parser2Tester(callback_type const &callback) : callback_{callback} {}

  bool operator()(sbe::PacketHeader const &) override { return true; }
  //
  void operator()(
      Trace<deribit::sbe::market_data::Instrument> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    dispatch(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::TradingStatusUpdate> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    dispatch(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::InstrumentInfo> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    dispatch(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::InstrumentRef> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    dispatch(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::BidPut> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    dispatch(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::AskPut> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    dispatch(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::BidQtyReduced> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    dispatch(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::AskQtyReduced> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    dispatch(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::BidDelete> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    dispatch(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::AskDelete> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    dispatch(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::TradeSummary> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    dispatch(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::Trade> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    dispatch(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::BlockTrade> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    dispatch(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::SnapshotHeader> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    dispatch(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::SnapshotTrailer> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    dispatch(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::EndOfCycle> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    dispatch(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::RetransmitRequest> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    dispatch(event, message_header, packet_header);
  }
  void operator()(
      Trace<deribit::sbe::market_data::RetransmitReject> const &event,
      deribit::sbe::market_data::MdMessageHeader const &message_header,
      sbe::PacketHeader const &packet_header) override {
    dispatch(event, message_header, packet_header);
  }

  template <typename U, typename MessageHeader, typename PacketHeader>
  void dispatch(Trace<U> const &event, MessageHeader const &message_header, PacketHeader const &packet_header) {
    if constexpr (std::is_invocable_v<callback_type, U, MessageHeader, PacketHeader>) {
      found_ = true;
      callback_(event, message_header, packet_header);
    } else {
      FAIL();
    }
  }

 private:
  callback_type const callback_;
  bool found_ = false;
};

}  // namespace starbase
}  // namespace roq
