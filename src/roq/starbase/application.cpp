/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/application.hpp"

#include "roq/starbase/flags/settings.hpp"

#include "roq/starbase/gateway/config.hpp"
#include "roq/starbase/gateway/controller.hpp"

using namespace std::literals;

namespace roq {
namespace starbase {

// === IMPLEMENTATION ===

int Application::main(args::Parser const &args) {
  flags::Settings settings{args};
  gateway::Config config{settings};
  auto context = server::create_io_context(settings);
  server::Trading<gateway::Controller>{settings, config, *context}.dispatch();
  return EXIT_SUCCESS;
}

}  // namespace starbase
}  // namespace roq
