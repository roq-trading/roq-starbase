/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include <catch2/catch_all.hpp>

#include "roq/starbase/sbe/parser.hpp"

namespace roq {
namespace starbase {

template <typename T>
struct ParserTester final : public sbe::Parser::Handler {
  using value_type = std::remove_cvref_t<T>;
  using callback_type = std::function<void(value_type const &, deribit_sbe_order::MessageHeader const &)>;

  static void dispatch(callback_type const &callback, auto const &message) {
    // XXX FIXME TODO catch2 block ???
    ParserTester handler{callback};
    auto res = sbe::Parser::dispatch(handler, std::span{reinterpret_cast<std::byte const *>(std::data(message)), std::size(message)}, {});
    CHECK(res == true);
    CHECK(handler.found_ == true);
  }

 protected:
  explicit ParserTester(callback_type const &callback) : callback_{callback} {}

  void operator()(Trace<deribit_sbe_order::Logon> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::LogonConf> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::Logout> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::LoggedOut> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::Heartbeat> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::TestRequest> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::ResendRequest> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::GapFill> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::Reject> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::NewOrderRequest> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::AmendOrderRequest> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::CancelOrderRequest> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::MassQuoteRequest> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::MassCancelRequest> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::MassQuoteCancelRequest> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::NewOrderResponse> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::NewOrderReject> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::AmendOrderResponse> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::AmendOrderReject> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::CancelOrderResponse> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::CancelOrderReject> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::MassQuoteResponse> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::MassQuoteReject> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::MassCancelResponse> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::MassCancelReject> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::OrderFilled> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::OrdersCanceled> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::OrderPlaced> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::MassQuoteOrdersPlaced> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::MassQuoteMmpTriggered> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::OrdersMmpTriggered> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::MassQuoteMmpUnfrozen> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::OrdersMmpUnfrozen> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit_sbe_order::DummyMessage> const &event, deribit_sbe_order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }

  template <typename U, typename MessageHeader>
  void dispatch(Trace<U> const &event, MessageHeader const &message_header) {
    if constexpr (std::is_invocable_v<callback_type, U, MessageHeader>) {
      found_ = true;
      callback_(event, message_header);
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
