/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/gateway/shared.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

namespace roq {
namespace starbase {
namespace gateway {

// === CONSTANTS ===

namespace {
auto const BUFFER_SIZE = 4096uz;
}

// === HELPERS ===

namespace {
auto get_multicast(auto &settings) {
  // XXX maybe check more flags?
  if (std::empty(settings.multicast.local_interface)) {
    return false;
  }
  if (std::empty(settings.multicast.channel_ids)) {
    log::fatal("Unexpected: --channel_ids is empty"sv);
  }
  if (std::empty(settings.multicast.config_file)) {
    log::fatal("Unexpected: --config_file is empty"sv);
  }
  log::info("Using multicast"sv);
  return true;
}
}  // namespace

// === IMPLEMENTATION ===

Shared::Shared(server::Dispatcher &dispatcher, Settings const &settings)
    : dispatcher{dispatcher}, api{API::create(settings)}, settings{settings}, rate_limiter{settings.request.limit, settings.request.limit_interval},
      symbols{settings.fix.market_data_max_subscriptions_per_stream}, buffer(BUFFER_SIZE), multicast_{get_multicast(settings)} {
}

std::string_view Shared::next_request_id() {
  auto request_id = ++request_id_;
  request_id_encode_buffer_.clear();
  fmt::format_to(std::back_inserter(request_id_encode_buffer_), "roq-{}"sv, request_id);
  return request_id_encode_buffer_;
}

}  // namespace gateway
}  // namespace starbase
}  // namespace roq
