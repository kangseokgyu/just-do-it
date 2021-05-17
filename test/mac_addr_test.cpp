#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "mac_addr.h"

TEST(MacAddr, MacAddr) {
  ASSERT_EQ(MacAddr(0),
            MacAddr(std::vector<uint8_t>(6, 0))); // 00:00:00:00:00:00
  ASSERT_EQ(MacAddr(281474976710655),
            MacAddr(std::vector<uint8_t>(6, 255))); // ff:ff:ff:ff:ff:ff
}

TEST(MacAddr, isMacFormatString) {
  ASSERT_TRUE(MacAddr::isMacFormat(std::string("00:00:00:00:00:00")));
  ASSERT_TRUE(MacAddr::isMacFormat(std::string("00-00-00-00-00-00")));
  ASSERT_TRUE(MacAddr::isMacFormat(std::string("ff-ff-ff-ff-ff-ff")));
  ASSERT_TRUE(MacAddr::isMacFormat(std::string("FF-FF-FF-FF-FF-FF")));

  ASSERT_FALSE(MacAddr::isMacFormat(std::string("")));
  ASSERT_FALSE(MacAddr::isMacFormat(std::string("00000000000")));
  ASSERT_FALSE(MacAddr::isMacFormat(std::string("0000000000000")));
  ASSERT_FALSE(MacAddr::isMacFormat(std::string("000000000000")));
  ASSERT_FALSE(MacAddr::isMacFormat(std::string("ffffffffffff")));
  ASSERT_FALSE(MacAddr::isMacFormat(std::string("ff=ff=ff=ff=ff=ff")));
  ASSERT_FALSE(MacAddr::isMacFormat(std::string("tt-tt-tt-tt-tt-tt")));
  ASSERT_FALSE(MacAddr::isMacFormat(std::string("aa-aa-aa-aa-aa-tt")));
}