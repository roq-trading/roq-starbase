/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/starbase/filter/settings.hpp"

using namespace std::literals;

namespace roq {
namespace starbase {
namespace filter {

// === IMPLEMENTATION ===

Settings::Settings(args::Parser const &) : flags::Flags{flags::Flags::create()}, multicast{flags::multicast::create()} {
}

}  // namespace filter
}  // namespace starbase
}  // namespace roq
