/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include "roq/flags/args.hpp"

#include "roq/starbase/dump/flags/flags.hpp"

namespace roq {
namespace starbase {
namespace dump {

struct Settings final : public flags::Flags {
  explicit Settings(args::Parser const &);
};

}  // namespace dump
}  // namespace starbase
}  // namespace roq
