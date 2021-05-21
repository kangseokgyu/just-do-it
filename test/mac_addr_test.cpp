#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "mac_addr.h"

TEST(MacAddr, MacAddr) {
  ASSERT_EQ(MacAddr(0),
            MacAddr(std::vector<uint8_t>(6, 0))); // 00:00:00:00:00:00
  ASSERT_EQ(MacAddr(0xff'ff'ff'ff'ff'ff),
            MacAddr(std::vector<uint8_t>(6, 255))); // ff:ff:ff:ff:ff:ff

  ASSERT_EQ(MacAddr(0),
            MacAddr(std::string("00:00:00:00:00:00"))); // 00:00:00:00:00:00
  ASSERT_EQ(MacAddr(0xff'ff'ff'ff'ff'ff),
            MacAddr(std::string("ff-ff-ff-ff-ff-ff"))); // ff:ff:ff:ff:ff:ff
  ASSERT_ANY_THROW(MacAddr(std::string("")));
  ASSERT_ANY_THROW(MacAddr(std::string("00000000000")));
  ASSERT_ANY_THROW(MacAddr(std::string("0000000000000")));
  ASSERT_ANY_THROW(MacAddr(std::string("000000000000")));
  ASSERT_ANY_THROW(MacAddr(std::string("ffffffffffff")));
  ASSERT_ANY_THROW(MacAddr(std::string("ff=ff=ff=ff=ff=ff")));
  ASSERT_ANY_THROW(MacAddr(std::string("tt-tt-tt-tt-tt-tt")));
  ASSERT_ANY_THROW(MacAddr(std::string("aa-aa-aa-aa-aa-tt")));
}

TEST(MacAddr, getter) {
  ASSERT_EQ(MacAddr(0).getString(), "00:00:00:00:00:00");
  ASSERT_EQ(MacAddr(0xff'ff'ff'ff'ff'ff).getString(), "ff:ff:ff:ff:ff:ff");
  ASSERT_EQ(MacAddr(0x11'22'33'44'55'66).getString(), "11:22:33:44:55:66");
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

TEST(MacAddr, isMacFormatVector) {
  ASSERT_TRUE(MacAddr::isMacFormat(std::vector<uint8_t>(6, 0)));
  ASSERT_TRUE(MacAddr::isMacFormat(std::vector<uint8_t>(6, 255)));

  ASSERT_FALSE(MacAddr::isMacFormat(std::vector<uint8_t>(0)));
  ASSERT_FALSE(MacAddr::isMacFormat(std::vector<uint8_t>(5)));
  ASSERT_FALSE(MacAddr::isMacFormat(std::vector<uint8_t>(200)));
}
