/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include "roq/starbase/filter/settings.hpp"

namespace roq {
namespace starbase {
namespace filter {

struct Controller final {
  explicit Controller(Settings const &);

  Controller(Controller const &) = delete;
  Controller(Controller &&) = delete;

  void dispatch();

 private:
  Settings const &settings_;
};

}  // namespace filter
}  // namespace starbase
}  // namespace roq
