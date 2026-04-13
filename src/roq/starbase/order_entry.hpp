/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <string>

#include "roq/utils/container.hpp"

#include "roq/utils/metrics/counter.hpp"
#include "roq/utils/metrics/latency.hpp"
#include "roq/utils/metrics/profile.hpp"

#include "roq/io/context.hpp"
#include "roq/io/net/connection_factory.hpp"
#include "roq/io/net/connection_manager.hpp"

#include "roq/core/download.hpp"

#include "roq/server.hpp"

#include "roq/starbase/account.hpp"
#include "roq/starbase/order_entry_state.hpp"
#include "roq/starbase/shared.hpp"

#include "roq/starbase/sbe/parser.hpp"

namespace roq {
namespace starbase {

struct OrderEntry final : public io::net::ConnectionManager::Handler, sbe::Parser::Handler {
  struct Handler {
    virtual void operator()(Trace<StreamStatus> const &) = 0;
    virtual void operator()(Trace<ExternalLatency> const &) = 0;
    virtual void operator()(Trace<TradeUpdate> const &, bool is_last, uint8_t user_id, std::string_view const &request_id) = 0;
  };

  OrderEntry(Handler &, io::Context &, uint16_t stream_id, Account &, Shared &);

  OrderEntry(OrderEntry const &) = delete;

  bool ready() const { return connection_status_ == ConnectionStatus::READY; }

  void operator()(Event<Start> const &);
  void operator()(Event<Stop> const &);
  void operator()(Event<Timer> const &);

  uint16_t operator()(Event<CreateOrder> const &, server::oms::Order const &, server::oms::RefData const &, std::string_view const &request_id);
  uint16_t operator()(
      Event<ModifyOrder> const &,
      server::oms::Order const &,
      server::oms::RefData const &,
      std::string_view const &request_id,
      std::string_view const &previous_request_id);
  uint16_t operator()(
      Event<CancelOrder> const &,
      server::oms::Order const &,
      server::oms::RefData const &,
      std::string_view const &request_id,
      std::string_view const &previous_request_id);

  uint16_t operator()(Event<CancelAllOrders> const &, std::string_view const &request_id);

  void operator()(metrics::Writer &) const;

  // sbe::Parser::Handler
  bool operator()(sbe::Frame const &) override;
  //
  void operator()(Trace<deribit_sbe_order::Logon> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::LogonConf> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::Logout> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::LoggedOut> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::Heartbeat> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::TestRequest> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::ResendRequest> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::GapFill> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::Reject> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::NewOrderRequest> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::AmendOrderRequest> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::CancelOrderRequest> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::MassQuoteRequest> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::MassCancelRequest> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::MassQuoteCancelRequest> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::NewOrderResponse> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::NewOrderReject> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::AmendOrderResponse> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::AmendOrderReject> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::CancelOrderResponse> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::CancelOrderReject> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::MassQuoteResponse> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::MassQuoteReject> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::MassCancelResponse> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::MassCancelReject> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::OrderFilled> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::OrdersCanceled> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::OrderPlaced> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::MassQuoteOrdersPlaced> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::MassQuoteMmpTriggered> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::OrdersMmpTriggered> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::MassQuoteMmpUnfrozen> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::OrdersMmpUnfrozen> const &, sbe::Frame const &) override;
  void operator()(Trace<deribit_sbe_order::DummyMessage> const &, sbe::Frame const &) override;

 protected:
  void operator()(io::net::ConnectionManager::Connected const &) override;
  void operator()(io::net::ConnectionManager::Disconnected const &) override;
  void operator()(io::net::ConnectionManager::Read const &) override;
  void operator()(io::net::ConnectionManager::Write const &) override;

 private:
  void operator()(ConnectionStatus, std::string_view const &reason = {});

  void send_logon();
  void send_logout(std::string_view const &text);
  void send_heartbeat(std::string_view const &test_req_id);
  void send_test_request(std::chrono::nanoseconds now);

  uint32_t download(OrderEntryState);

  // utilities

  template <typename T>
  uint64_t send(T const &event);

  template <typename T>
  uint64_t send(T const &event, std::chrono::nanoseconds sending_time);

  Handler &handler_;
  // config
  uint16_t const stream_id_;
  std::string const name_;
  // connection
  std::unique_ptr<io::net::ConnectionFactory> const connection_factory_;
  std::unique_ptr<io::net::ConnectionManager> const connection_manager_;
  // buffers
  std::vector<std::byte> decode_buffer_;
  std::vector<std::byte> encode_buffer_2_;
  std::string encode_buffer_;
  // metrics
  struct {
    utils::metrics::Counter disconnect;
  } counter_;
  struct {
    utils::metrics::Profile parse, position_report, execution_report, order_cancel_reject, reject, order_mass_cancel_report;
  } profile_;
  struct {
    utils::metrics::Latency ping;
  } latency_;
  // state
  struct {
    uint64_t msg_seq_num = {};
  } outbound_;
  struct {
    uint64_t msg_seq_num = {};
  } inbound_;
  // account
  Account &account_;
  // cache
  Shared &shared_;
  // state
  ConnectionStatus connection_status_ = {};

  // state
  bool ready_ = false;
  std::chrono::nanoseconds next_heartbeat_ = {};
  core::Download<OrderEntryState> download_;
  std::chrono::nanoseconds last_logon_or_heartbeat_ = {};
  // EXPERIMENTAL
  utils::unordered_map<uint64_t, RequestId> msg_seq_num_to_request_id_;
  std::chrono::nanoseconds test_disconnect_time_ = {};
  std::chrono::nanoseconds test_logon_time_ = {};
};

}  // namespace starbase
}  // namespace roq
