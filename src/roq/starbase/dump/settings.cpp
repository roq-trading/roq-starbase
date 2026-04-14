/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/dump/settings.hpp"

using namespace std::literals;

namespace roq {
namespace starbase {
namespace dump {

// === IMPLEMENTATION ===

Settings::Settings(args::Parser const &) : flags::Flags{flags::Flags::create()} {
}

}  // namespace dump
}  // namespace starbase
}  // namespace roq
