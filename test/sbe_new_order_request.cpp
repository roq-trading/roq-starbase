/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include <catch2/catch_all.hpp>

#include <fmt/format.h>

#include <cmath>
#include <span>

#include "parser_tester.hpp"

#include "roq/logging.hpp"

#include "roq/starbase/protocol/sbe/map.hpp"

using namespace std::literals;

using namespace Catch::literals;

using namespace roq;
using namespace roq::starbase;

using value_type = deribit::sbe::order::NewOrderRequest;

inline double to_double(auto &value) {
  return map(value).template get<double>();
}

TEST_CASE("simple", "[sbe_new_order_request]") {
  constexpr auto message =
      "\xdb"                              // protocol_id
      "\x00"                              // flags=0
      "\x5f\x00"                          // message_length
      "\x64\x00"                          // message_type_id
      "\x01\x00"                          // version
      "\xfd\x75\x03\x00\x00\x00\x00\x00"  // sequence_number
      "\xb1\xf8\x02\x00\x00\x00\x00\x00"  // last_processed_seq_no
      "\x38\x5a\x0a\x9f\xd4\x13\xa5\x18"  // send_time_ns
      //
      "\x3c\xab\x3f\x68\x00\x00\x00\x00"      // client_order_id
      "\x8a\xf5\x02\x00\x00\x00\x00\x00"      // correlation_id
      "\x42\xa5\x08\x00\x00\x00\x00\x00"      // instrument_id
      "\x00\x23\x66\x30\x00\x00\x00\x00"      // price
      "\x00\x88\x52\x6a\x74\x00\x00\x00\xf7"  // quantity
      "\x00\x00\x00\x00\x00\x00\x00\x80\x00"  // show_qty
      "\x00\x00\x00\x00\x00\x00\x00\x80"      // self_match_prevention_id
      "\x01"                                  // side
      "\x00"                                  // time_in_force
      "\x06\x00"                              // flags
      "\x00"sv;                               // self_trading_mode
  static_assert(std::size(message) == 95);
  auto helper = [](value_type const &obj, deribit::sbe::order::MessageHeader const &message_header) {
    CHECK(message_header.protocolId() == 0xdb);
    // CHECK(message_header.flags().rawValue() == 0x0);
    CHECK(message_header.messageLength() == 0x5f);
    CHECK(message_header.messageTypeId() == 0x64);
    CHECK(message_header.version() == 0x1);
    CHECK(message_header.sequenceNumber() == 0x375fd);
    CHECK(message_header.lastProcessedSeqNo() == 0x2f8b1);
    CHECK(message_header.sendTimeNs() == 0x18a513d49f0a5a38);
    //
    CHECK(obj.clientOrderId() == 0x683fab3c);
    CHECK(obj.correlationId() == 0x2f58a);
    CHECK(obj.instrumentId() == 0x8a542);
    CHECK(to_double(const_cast<value_type &>(obj).price()) == 0.812_a);
    CHECK(to_double(const_cast<value_type &>(obj).quantity()) == 500.0_a);
    CHECK(std::isnan(to_double(const_cast<value_type &>(obj).showQty())));
    CHECK(obj.selfMatchPreventionId() == std::numeric_limits<int64_t>::min());
    CHECK(obj.side() == 0x1);
    CHECK(obj.timeInForce() == 0x0);
    CHECK(const_cast<value_type &>(obj).flags().rawValue() == 0x6);
    CHECK(obj.selfTradingMode() == 0x0);
  };
  ParserTester<value_type>::dispatch(helper, message);
}
