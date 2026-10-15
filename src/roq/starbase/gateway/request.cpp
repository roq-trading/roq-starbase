/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/gateway/request.hpp"

using namespace std::literals;

namespace roq {
namespace starbase {
namespace gateway {

// === IMPLEMENTATION ===

Request::Request(Shared &shared) : currencies{*this}, instruments{*this}, shared_{shared} {
}

bool Request::ready() const {
  return currencies.ready() && instruments.ready();
}

bool Request::can_request(TraceInfo const &trace_info) {
  return shared_.rate_limiter.can_request(trace_info);
}

}  // namespace gateway
}  // namespace starbase
}  // namespace roq
