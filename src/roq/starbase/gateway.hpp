/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "roq/server.hpp"

#include "roq/utils/container.hpp"

#include "roq/io/context.hpp"

#include "roq/starbase/account.hpp"
#include "roq/starbase/config.hpp"
#include "roq/starbase/market_data.hpp"
#include "roq/starbase/market_data_snapshot.hpp"
#include "roq/starbase/order_entry.hpp"
#include "roq/starbase/request.hpp"
#include "roq/starbase/settings.hpp"
#include "roq/starbase/shared.hpp"

namespace roq {
namespace starbase {

struct Gateway final : public server::Handler, public OrderEntry::Handler, public MarketData::Handler, public MarketDataSnapshot::Handler {
  Gateway(server::Dispatcher &, Settings const &, Config const &, io::Context &);

  Gateway(Gateway const &) = delete;

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

}  // namespace starbase
}  // namespace roq
