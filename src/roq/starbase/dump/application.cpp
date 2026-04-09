/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/dump/application.hpp"

#include "roq/logging.hpp"

#include "roq/starbase/dump/controller.hpp"
#include "roq/starbase/dump/settings.hpp"

using namespace std::literals;

namespace roq {
namespace starbase {
namespace dump {

// === IMPLEMENTATION ===

int Application::main(args::Parser const &args) {
  Settings settings{args};
  auto params = args.params();
  if (std::size(params) != 1) {
    log::fatal("Expected exactly one argument"sv);
  }
  Controller{settings, params[0]}.dispatch();
  return EXIT_SUCCESS;
}

}  // namespace dump
}  // namespace starbase
}  // namespace roq
