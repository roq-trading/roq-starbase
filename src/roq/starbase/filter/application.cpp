/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/filter/application.hpp"

#include "roq/logging.hpp"

#include "roq/starbase/filter/controller.hpp"
#include "roq/starbase/filter/settings.hpp"

using namespace std::literals;

namespace roq {
namespace starbase {
namespace filter {

// === IMPLEMENTATION ===

int Application::main(args::Parser const &args) {
  Settings settings{args};
  Controller{settings}.dispatch();
  return EXIT_SUCCESS;
}

}  // namespace filter
}  // namespace starbase
}  // namespace roq
