/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/gateway/controller.hpp"

#include "roq/server/oms/exceptions.hpp"

using namespace std::literals;

namespace roq {
namespace starbase {
namespace gateway {

// === HELPERS ===

namespace {
auto create_master_account(auto &config) {
  std::string_view result = config.get_master_account();
  if (std::empty(result)) {
    log::fatal("Market data requires a master account"sv);
  }
  return result;
}

template <typename R>
R create_accounts(auto &config) {
  using result_type = std::remove_cvref_t<R>;
  result_type result;
  for (auto &[_, account] : config.accounts) {
    auto obj = std::make_unique<Account>(config, account.name);
    result.try_emplace(account.name, std::move(obj));
  }
  return result;
}

template <typename R>
R create_order_entry(auto &gateway, auto &context, auto &stream_id, auto &accounts, auto &shared) {
  using result_type = std::remove_cvref_t<R>;
  result_type result;
  for (auto &[_, item] : accounts) {
    auto &account = *item;
    auto obj = std::make_unique<OrderEntry>(gateway, context, ++stream_id, account, shared);
    result.try_emplace(account.name, std::move(obj));
  }
  return result;
}

auto create_market_data_snapshot(auto &gateway, auto &context, auto &stream_id, auto &shared) {
  if (shared.has_multicast()) {
    return std::make_unique<MarketDataSnapshot>(gateway, context, stream_id, shared);
  }
  return std::unique_ptr<MarketDataSnapshot>{};
}

auto create_market_data(auto &gateway, auto &context, auto &stream_id, auto &shared) {
  if (shared.has_multicast()) {
    return std::make_unique<MarketData>(gateway, context, stream_id, shared);
  }
  return std::unique_ptr<MarketData>{};
}
}  // namespace

// === IMPLEMENTATION ===

std::unique_ptr<server::Handler> Controller::create(server::Dispatcher &dispatcher, Settings const &settings, Config const &config, io::Context &context) {
  return std::make_unique<Controller>(dispatcher, settings, config, context);
}

uint8_t Controller::parse_api(Settings const &) {
  return {};
}

Controller::Controller(server::Dispatcher &dispatcher, Settings const &settings, Config const &config, io::Context &context)
    : dispatcher_{dispatcher}, master_account_{create_master_account(config)}, context_{context}, shared_{dispatcher_, settings},
      accounts_{create_accounts<decltype(accounts_)>(config)}, request_{shared_},
      order_entry_{create_order_entry<decltype(order_entry_)>(*this, context_, stream_id_, accounts_, shared_)},
      market_data_snapshot_{create_market_data_snapshot(*this, context_, ++stream_id_, shared_)},
      market_data_{create_market_data(*this, context_, ++stream_id_, shared_)} {
  if (std::empty(master_account_) && !settings.misc.disable_master_account_check) {
    log::fatal("A master account is always required (due to FIX logon)"sv);
  }
  if (!settings.fix.cancel_on_disconnect) {
    log::warn("Orders will *NOT* be cancelled on disconnect"sv);
  }
}

// server::Handler

void Controller::operator()(Trace<Start> const &event) {
  log::info("Starting..."sv);
  dispatch(event);
}

void Controller::operator()(Trace<Stop> const &event) {
  log::info("Stopping..."sv);
  dispatch(event);
}

void Controller::operator()(Trace<Timer> const &event) {
  dispatch(event);
}

void Controller::operator()(Trace<server::Refresh> const &) {
}

void Controller::operator()(Trace<Connected> const &, [[maybe_unused]] uint8_t user_id) {
}

void Controller::operator()(Trace<Disconnected> const &, [[maybe_unused]] uint8_t user_id) {
}

void Controller::operator()(Trace<Subscribe> const &event) {
  auto &[trace_info, subscribe] = event;
  std::vector<Symbol> symbols;
  for (auto &item : subscribe.symbols) {
    if (shared_.all_symbols.emplace(item).second) {
      symbols.emplace_back(item);
    } else {
      log::warn(R"(*** DUPLICATE SUBSCRIPTION *** (symbol="{}")"sv, item);
    }
  }
}

void Controller::operator()(Trace<Control> const &event) {
  auto &[trace_info, control] = event;
  switch (control.action) {
    using enum Action;
    case UNDEFINED:
      assert(false);
      break;
    case ENABLE:
      dispatcher_(State::ENABLED);
      break;
    case DISABLE:
      dispatcher_(State::DISABLED);
      break;
  }
}

void Controller::operator()(Trace<server::oms::OrderActionBatchBegin> const &event) {
  dispatch_order_action(event);
}

void Controller::operator()(Trace<server::oms::OrderActionBatchCommit> const &event) {
  dispatch_order_action(event);
}

void Controller::operator()(Trace<server::oms::OrderActionBatchRollback> const &event) {
  dispatch_order_action(event);
}

uint16_t Controller::operator()(
    Trace<CreateOrder> const &event, server::oms::Order const &order, server::oms::RefData const &ref_data, std::string_view const &request_id) {
  return dispatch_order_action(event, order, ref_data, request_id);
}

uint16_t Controller::operator()(
    Trace<ModifyOrder> const &event,
    server::oms::Order const &order,
    server::oms::RefData const &ref_data,
    std::string_view const &request_id,
    std::string_view const &previous_request_id) {
  return dispatch_order_action(event, order, ref_data, request_id, previous_request_id);
}

uint16_t Controller::operator()(
    Trace<CancelOrder> const &event,
    server::oms::Order const &order,
    server::oms::RefData const &ref_data,
    std::string_view const &request_id,
    std::string_view const &previous_request_id) {
  return dispatch_order_action(event, order, ref_data, request_id, previous_request_id);
}

uint16_t Controller::operator()(Trace<CancelAllOrders> const &event, std::string_view const &request_id) {
  return dispatch_order_action(event, request_id);
}

uint16_t Controller::operator()(Trace<MassQuote> const &) {
  throw server::oms::NotSupported{"not supported"sv};
}

uint16_t Controller::operator()(Trace<CancelQuotes> const &) {
  throw server::oms::NotSupported{"not supported"sv};
}

void Controller::operator()(metrics::Writer &writer) const {
  dispatch_helper(*this, writer);
}

// utilities

template <typename... Args>
void Controller::dispatch(Args &&...args) {
  dispatch_helper(*this, std::forward<Args>(args)...);
}

template <typename... Args>
void Controller::dispatch_helper(auto &self, Args &&...args) {
  auto helper = [&](auto &target) {
    if constexpr (std::is_const_v<decltype(self)>) {
      dynamic_cast<server::Stream const &>(target)(std::forward<Args>(args)...);
    } else {
      dynamic_cast<server::Stream &>(target)(std::forward<Args>(args)...);
    }
  };
  for (auto &[_, item] : self.order_entry_) {
    helper(*item);
  }
  if (self.market_data_snapshot_) {
    helper(*self.market_data_snapshot_);
  }
  if (self.market_data_) {
    helper(*self.market_data_);
  }
}

Account &Controller::get_account(std::string_view const &account) {
  auto iter = accounts_.find(account);
  if (iter == std::end(accounts_)) [[unlikely]] {
    throw RuntimeError{R"(Unknown account="{}")"sv, account};
  }
  return *(*iter).second;
}

template <typename T, typename... Args>
uint16_t Controller::dispatch_order_action(Trace<T> const &event, Args &&...args) {
  auto &[trace_info, value] = event;
  auto iter = order_entry_.find(value.account);
  if (iter == std::end(order_entry_)) [[unlikely]] {
    throw RuntimeError{R"(Unknown account="{}")"sv, value.account};
  }
  auto &stream = dynamic_cast<server::OrderActionStream &>(*(*iter).second);
  stream(event, args...);
  return stream.stream_id();
}

}  // namespace gateway
}  // namespace starbase
}  // namespace roq
