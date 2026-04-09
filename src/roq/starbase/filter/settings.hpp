/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include "roq/flags/args.hpp"

#include "roq/starbase/filter/flags/flags.hpp"
#include "roq/starbase/filter/flags/multicast.hpp"

namespace roq {
namespace starbase {
namespace filter {

struct Settings final : public flags::Flags {
  explicit Settings(args::Parser const &);

  flags::multicast multicast;
};

}  // namespace filter
}  // namespace starbase
}  // namespace roq
