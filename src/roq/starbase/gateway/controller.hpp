/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include "roq/compat.hpp"

#include <memory>
#include <string>
#include <vector>

#include "roq/server.hpp"

#include "roq/utils/container.hpp"

#include "roq/io/context.hpp"

#include "roq/starbase/gateway/account.hpp"
#include "roq/starbase/gateway/config.hpp"
#include "roq/starbase/gateway/market_data.hpp"
#include "roq/starbase/gateway/market_data_snapshot.hpp"
#include "roq/starbase/gateway/order_entry.hpp"
#include "roq/starbase/gateway/request.hpp"
#include "roq/starbase/gateway/settings.hpp"
#include "roq/starbase/gateway/shared.hpp"

namespace roq {
namespace starbase {
namespace gateway {

struct Controller final : public server::Handler, public OrderEntry::Handler, public MarketData::Handler, public MarketDataSnapshot::Handler {
  ROQ_PUBLIC static std::unique_ptr<server::Handler> create(server::Dispatcher &, Settings const &, Config const &, io::Context &);

  Controller(server::Dispatcher &, Settings const &, Config const &, io::Context &);

  Controller(Controller const &) = delete;

 protected:
  // server::Handler

  void operator()(Event<Start> const &) override;
  void operator()(Event<Stop> const &) override;
  void operator()(Event<Timer> const &) override;
  void operator()(Event<Control> const &) override;
  void operator()(Event<server::Refresh> const &) override;
  void operator()(Event<Connected> const &) override;
  void operator()(Event<Disconnected> const &) override;

  void operator()(Event<Subscribe> const &) override;

  uint16_t operator()(Event<CreateOrder> const &, server::oms::Order const &, server::oms::RefData const &, std::string_view const &request_id) override;
  uint16_t operator()(
      Event<ModifyOrder> const &,
      server::oms::Order const &,
      server::oms::RefData const &,
      std::string_view const &request_id,
      std::string_view const &previous_request_id) override;
  uint16_t operator()(
      Event<CancelOrder> const &,
      server::oms::Order const &,
      server::oms::RefData const &,
      std::string_view const &request_id,
      std::string_view const &previous_request_id) override;

  uint16_t operator()(Event<CancelAllOrders> const &, std::string_view const &request_id) override;

  uint16_t operator()(Event<MassQuote> const &) override;

  uint16_t operator()(Event<CancelQuotes> const &) override;

  void operator()(metrics::Writer &) const override;

  // streams

  void operator()(Trace<StreamStatus> const &) override;
  void operator()(Trace<ExternalLatency> const &) override;
  void operator()(Trace<ReferenceData> const &, bool is_last) override;
  void operator()(Trace<MarketStatus> const &, bool is_last) override;
  void operator()(Trace<MarketByOrderUpdate> const &, bool is_last) override;
  void operator()(Trace<TradeSummary> const &, bool is_last) override;
  void operator()(Trace<StatisticsUpdate> const &, bool is_last) override;
  void operator()(Trace<TradeUpdate> const &, bool is_last, uint8_t user_id, std::string_view const &request_id) override;

  // utilities

  template <typename... Args>
  void dispatch(Args &&...);

  template <typename... Args>
  static void dispatch_helper(auto &self, Args &&...);

  Account &get_account(std::string_view const &account);

  OrderEntry &get_order_entry(std::string_view const &account);

 private:
  server::Dispatcher &dispatcher_;
  // config
  std::string const master_account_;
  // accounts
  utils::unordered_map<std::string, std::unique_ptr<Account>> accounts_;
  // io
  io::Context &context_;
  // shared
  Shared shared_;
  // seed
  uint16_t stream_id_ = {};
  //
  Request request_;
  // streams
  utils::unordered_map<std::string, std::unique_ptr<OrderEntry>> order_entry_;
  std::unique_ptr<MarketDataSnapshot> market_data_snapshot_;
  std::unique_ptr<MarketData> market_data_;
  // cache
  std::vector<MBOUpdate> orders_;
};

}  // namespace gateway
}  // namespace starbase
}  // namespace roq
