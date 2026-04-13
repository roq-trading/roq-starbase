/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include <catch2/catch_all.hpp>

#include "roq/starbase/sbe/parser_2.hpp"

namespace roq {
namespace starbase {

template <typename T>
struct Parser2Tester final : public sbe::Parser2::Handler {
  using value_type = std::remove_cvref_t<T>;
  using callback_type = std::function<void(value_type const &, deribit_sbe_market_data::MdMessageHeader const &, sbe::Frame const &)>;

  static void dispatch(callback_type const &callback, auto const &message) {
    // XXX FIXME TODO catch2 block ???
    Parser2Tester handler{callback};
    auto res = sbe::Parser2::dispatch(handler, std::span{reinterpret_cast<std::byte const *>(std::data(message)), std::size(message)}, {});
    CHECK(res == true);
    CHECK(handler.found_ == true);
  }

 protected:
  explicit Parser2Tester(callback_type const &callback) : callback_{callback} {}

  bool operator()(sbe::Frame const &) { return true; }
  //
  void operator()(
      Trace<deribit_sbe_market_data::Instrument> const &event,
      deribit_sbe_market_data::MdMessageHeader const &message_header,
      sbe::Frame const &frame) override {
    dispatch(event, message_header, frame);
  }
  void operator()(
      Trace<deribit_sbe_market_data::TradingStatusUpdate> const &event,
      deribit_sbe_market_data::MdMessageHeader const &message_header,
      sbe::Frame const &frame) override {
    dispatch(event, message_header, frame);
  }
  void operator()(
      Trace<deribit_sbe_market_data::InstrumentInfo> const &event,
      deribit_sbe_market_data::MdMessageHeader const &message_header,
      sbe::Frame const &frame) override {
    dispatch(event, message_header, frame);
  }
  void operator()(
      Trace<deribit_sbe_market_data::InstrumentRef> const &event,
      deribit_sbe_market_data::MdMessageHeader const &message_header,
      sbe::Frame const &frame) override {
    dispatch(event, message_header, frame);
  }
  void operator()(
      Trace<deribit_sbe_market_data::BidPut> const &event, deribit_sbe_market_data::MdMessageHeader const &message_header, sbe::Frame const &frame) override {
    dispatch(event, message_header, frame);
  }
  void operator()(
      Trace<deribit_sbe_market_data::AskPut> const &event, deribit_sbe_market_data::MdMessageHeader const &message_header, sbe::Frame const &frame) override {
    dispatch(event, message_header, frame);
  }
  void operator()(
      Trace<deribit_sbe_market_data::BidQtyReduced> const &event,
      deribit_sbe_market_data::MdMessageHeader const &message_header,
      sbe::Frame const &frame) override {
    dispatch(event, message_header, frame);
  }
  void operator()(
      Trace<deribit_sbe_market_data::AskQtyReduced> const &event,
      deribit_sbe_market_data::MdMessageHeader const &message_header,
      sbe::Frame const &frame) override {
    dispatch(event, message_header, frame);
  }
  void operator()(
      Trace<deribit_sbe_market_data::BidDelete> const &event,
      deribit_sbe_market_data::MdMessageHeader const &message_header,
      sbe::Frame const &frame) override {
    dispatch(event, message_header, frame);
  }
  void operator()(
      Trace<deribit_sbe_market_data::AskDelete> const &event,
      deribit_sbe_market_data::MdMessageHeader const &message_header,
      sbe::Frame const &frame) override {
    dispatch(event, message_header, frame);
  }
  void operator()(
      Trace<deribit_sbe_market_data::TradeSummary> const &event,
      deribit_sbe_market_data::MdMessageHeader const &message_header,
      sbe::Frame const &frame) override {
    dispatch(event, message_header, frame);
  }
  void operator()(
      Trace<deribit_sbe_market_data::Trade> const &event, deribit_sbe_market_data::MdMessageHeader const &message_header, sbe::Frame const &frame) override {
    dispatch(event, message_header, frame);
  }
  void operator()(
      Trace<deribit_sbe_market_data::BlockTrade> const &event,
      deribit_sbe_market_data::MdMessageHeader const &message_header,
      sbe::Frame const &frame) override {
    dispatch(event, message_header, frame);
  }
  void operator()(
      Trace<deribit_sbe_market_data::SnapshotHeader> const &event,
      deribit_sbe_market_data::MdMessageHeader const &message_header,
      sbe::Frame const &frame) override {
    dispatch(event, message_header, frame);
  }
  void operator()(
      Trace<deribit_sbe_market_data::SnapshotTrailer> const &event,
      deribit_sbe_market_data::MdMessageHeader const &message_header,
      sbe::Frame const &frame) override {
    dispatch(event, message_header, frame);
  }
  void operator()(
      Trace<deribit_sbe_market_data::EndOfCycle> const &event,
      deribit_sbe_market_data::MdMessageHeader const &message_header,
      sbe::Frame const &frame) override {
    dispatch(event, message_header, frame);
  }
  void operator()(
      Trace<deribit_sbe_market_data::RetransmitRequest> const &event,
      deribit_sbe_market_data::MdMessageHeader const &message_header,
      sbe::Frame const &frame) override {
    dispatch(event, message_header, frame);
  }
  void operator()(
      Trace<deribit_sbe_market_data::RetransmitReject> const &event,
      deribit_sbe_market_data::MdMessageHeader const &message_header,
      sbe::Frame const &frame) override {
    dispatch(event, message_header, frame);
  }

  template <typename U, typename MessageHeader, typename Frame>
  void dispatch(Trace<U> const &event, MessageHeader const &message_header, Frame const &frame) {
    if constexpr (std::is_invocable_v<callback_type, U, MessageHeader, Frame>) {
      found_ = true;
      callback_(event, message_header, frame);
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
