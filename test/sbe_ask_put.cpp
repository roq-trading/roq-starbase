/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include <catch2/catch_all.hpp>

#include <fmt/format.h>

#include <cmath>
#include <span>

#include "parser_2_tester.hpp"

using namespace std::literals;

using namespace Catch::literals;

using namespace roq;
using namespace roq::starbase;

using value_type = deribit::sbe::market_data::AskPut;

TEST_CASE("simple", "[sbe_ask_put]") {
  constexpr auto message =
      "\x9d\xad\x06\xc4\x0c\x14\xa5\x18"  // sending_time
      "\xa5\x58\x00\x00\x00\x00\x00\x00"  // seq_num
      "\x35\xaf\x00\x00"                  // channel_id=44853
      "\x01\x00"                          // type=snapshot(1)
      "\x01\x00"                          // message_count=1
      //
      "\x30\x00"                          // message_length=48
      "\x15\x00"                          // template_id=AskPut(21)
      "\x00\x00"                          // version=0
      "\x03\x00"                          // flags=???
      "\x97\x01\x06\xc4\x0c\x14\xa5\x18"  // transact_time
      //
      "\x00\x00\x80\xa2\xc1\x5f\x56\x02"     // order_id
      "\xf9\xd9\x04\x00\x00\x00\x00\x00"     // instrument_id
      "\x0a\x00\x00\x00\x00\x00\x00\x00"     // quantity_mantissa
      "\x00\x0f\x26\x40\x54\x04\x00\x00"sv;  // price
  static_assert(std::size(message) == 72);
  auto helper = [](value_type const &obj, deribit::sbe::market_data::MdMessageHeader const &message_header, protocol::sbe::PacketHeader const &packet_header) {
    CHECK(packet_header.sending_time == std::chrono::nanoseconds{0x18a5140cc406ad9d});
    CHECK(packet_header.seq_num == 0x58a5);
    CHECK(packet_header.channel_id == 0xaf35);
    CHECK(packet_header.type == 0x01);
    CHECK(packet_header.message_count == 0x01);
    //
    CHECK(message_header.messageLength() == 0x30);
    CHECK(message_header.templateId() == 0x15);
    CHECK(message_header.version() == 0x0);
    CHECK(const_cast<deribit::sbe::market_data::MdMessageHeader &>(message_header).flags().rawValue() == 0x3);
    CHECK(message_header.transactTime() == 0x18a5140cc4060197);
    //
    CHECK(obj.orderId() == 0x02565fc1a2800000);
    CHECK(obj.instrumentId() == 0x4d9f9);
    CHECK(obj.quantityMantissa() == 0xa);
    CHECK(const_cast<value_type &>(obj).price().price9() == 0x45440260f00);
  };
  Parser2Tester<value_type>::dispatch(helper, message);
}
