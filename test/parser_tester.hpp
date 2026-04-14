/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include <catch2/catch_all.hpp>

#include "roq/starbase/sbe/parser.hpp"

namespace roq {
namespace starbase {

template <typename T>
struct ParserTester final : public sbe::Parser::Handler {
  using value_type = std::remove_cvref_t<T>;
  using callback_type = std::function<void(value_type const &, deribit::sbe::order::MessageHeader const &)>;

  static void dispatch(callback_type const &callback, auto const &message) {
    // XXX FIXME TODO catch2 block ???
    ParserTester handler{callback};
    auto res = sbe::Parser::dispatch(handler, std::span{reinterpret_cast<std::byte const *>(std::data(message)), std::size(message)}, {});
    CHECK(res == true);
    CHECK(handler.found_ == true);
  }

 protected:
  explicit ParserTester(callback_type const &callback) : callback_{callback} {}

  void operator()(Trace<deribit::sbe::order::Logon> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::LogonConf> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::Logout> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::LoggedOut> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::Heartbeat> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::TestRequest> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::ResendRequest> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::GapFill> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::Reject> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::NewOrderRequest> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::AmendOrderRequest> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::CancelOrderRequest> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::MassQuoteRequest> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::MassCancelRequest> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::MassQuoteCancelRequest> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::NewOrderResponse> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::NewOrderReject> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::AmendOrderResponse> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::AmendOrderReject> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::CancelOrderResponse> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::CancelOrderReject> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::MassQuoteResponse> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::MassQuoteReject> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::MassCancelResponse> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::MassCancelReject> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::OrderFilled> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::OrdersCanceled> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::OrderPlaced> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::MassQuoteOrdersPlaced> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::MassQuoteMmpTriggered> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::OrdersMmpTriggered> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::MassQuoteMmpUnfrozen> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::OrdersMmpUnfrozen> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
    dispatch(event, message_header);
  }
  void operator()(Trace<deribit::sbe::order::DummyMessage> const &event, deribit::sbe::order::MessageHeader const &message_header) override {
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
