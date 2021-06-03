#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "mac_addr.h"

TEST(mac_addr, mac_addr) {
  ASSERT_EQ(mac_addr(0),
            mac_addr(std::vector<uint8_t>(6, 0))); // 00:00:00:00:00:00
  ASSERT_EQ(mac_addr(0xff'ff'ff'ff'ff'ff),
            mac_addr(std::vector<uint8_t>(6, 255))); // ff:ff:ff:ff:ff:ff

  ASSERT_EQ(mac_addr(0),
            mac_addr(std::string("00:00:00:00:00:00"))); // 00:00:00:00:00:00
  ASSERT_EQ(mac_addr(0xff'ff'ff'ff'ff'ff),
            mac_addr(std::string("ff-ff-ff-ff-ff-ff"))); // ff:ff:ff:ff:ff:ff
  ASSERT_ANY_THROW(mac_addr(std::string("")));
  ASSERT_ANY_THROW(mac_addr(std::string("00000000000")));
  ASSERT_ANY_THROW(mac_addr(std::string("0000000000000")));
  ASSERT_ANY_THROW(mac_addr(std::string("000000000000")));
  ASSERT_ANY_THROW(mac_addr(std::string("ffffffffffff")));
  ASSERT_ANY_THROW(mac_addr(std::string("ff=ff=ff=ff=ff=ff")));
  ASSERT_ANY_THROW(mac_addr(std::string("tt-tt-tt-tt-tt-tt")));
  ASSERT_ANY_THROW(mac_addr(std::string("aa-aa-aa-aa-aa-tt")));
}

TEST(mac_addr, getter) {
  ASSERT_EQ(mac_addr(0).getString(), "00:00:00:00:00:00");
  ASSERT_EQ(mac_addr(0xff'ff'ff'ff'ff'ff).getString(), "ff:ff:ff:ff:ff:ff");
  ASSERT_EQ(mac_addr(0x11'22'33'44'55'66).getString(), "11:22:33:44:55:66");
}

TEST(mac_addr, isMacFormatString) {
  ASSERT_TRUE(mac_addr::is_mac_format(std::string("00:00:00:00:00:00")));
  ASSERT_TRUE(mac_addr::is_mac_format(std::string("00-00-00-00-00-00")));
  ASSERT_TRUE(mac_addr::is_mac_format(std::string("ff-ff-ff-ff-ff-ff")));
  ASSERT_TRUE(mac_addr::is_mac_format(std::string("FF-FF-FF-FF-FF-FF")));

  ASSERT_FALSE(mac_addr::is_mac_format(std::string("")));
  ASSERT_FALSE(mac_addr::is_mac_format(std::string("00000000000")));
  ASSERT_FALSE(mac_addr::is_mac_format(std::string("0000000000000")));
  ASSERT_FALSE(mac_addr::is_mac_format(std::string("000000000000")));
  ASSERT_FALSE(mac_addr::is_mac_format(std::string("ffffffffffff")));
  ASSERT_FALSE(mac_addr::is_mac_format(std::string("ff=ff=ff=ff=ff=ff")));
  ASSERT_FALSE(mac_addr::is_mac_format(std::string("tt-tt-tt-tt-tt-tt")));
  ASSERT_FALSE(mac_addr::is_mac_format(std::string("aa-aa-aa-aa-aa-tt")));
}

TEST(mac_addr, isMacFormatVector) {
  ASSERT_TRUE(mac_addr::is_mac_format(std::vector<uint8_t>(6, 0)));
  ASSERT_TRUE(mac_addr::is_mac_format(std::vector<uint8_t>(6, 255)));

  ASSERT_FALSE(mac_addr::is_mac_format(std::vector<uint8_t>(0)));
  ASSERT_FALSE(mac_addr::is_mac_format(std::vector<uint8_t>(5)));
  ASSERT_FALSE(mac_addr::is_mac_format(std::vector<uint8_t>(200)));
}
