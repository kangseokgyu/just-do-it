#include "mac_addr.h"

#include <list>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include <fmt/format.h>
#include <range/v3/core.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/remove_if.hpp>

std::list<char> delimeters = {':', '-'};

auto is_delimeter = [](char c) {
  for (auto d : delimeters) {
    if (c == d) {
      return true;
    }
  }
  return false;
};

mac_addr::mac_addr() {}

mac_addr::mac_addr(const uint64_t &m) {
  if (m > BROADCAST_MAC)
    throw std::runtime_error(
        fmt::format("MacAddress -- The MAC address is too big. ({:012x})", m));
  m_ = m;
}

mac_addr::mac_addr(const std::vector<uint8_t> m) {
  if (is_mac_format(m)) {
    m_ = ranges::accumulate(
        m, (uint64_t)0,
        [](const uint64_t &mac, const uint8_t &b) { return mac << 8 | b; });
  } else {
    std::stringstream ss;
    ss << ranges::views::all(m);
    throw std::runtime_error(
        fmt::format("MacAddress -- Wrong Format. ({})", ss.str()));
  }
}

mac_addr::mac_addr(const std::string &m) {
  if (is_mac_format(m)) {
    auto ret =
        m | ranges::views::remove_if(is_delimeter) | ranges::to<std::vector>();
    m_ = std::stoul(ret.data(), nullptr, 16);
  } else {
    throw std::runtime_error(
        fmt::format("MacAddress -- Wrong Format. ({})", m));
  }
}

uint64_t mac_addr::get() const { return m_; }

std::string mac_addr::getString() const {
  std::string ret = "";
  std::string tmp = "";

  tmp = fmt::format("{:02x}", m_ % 256);
  ret.insert(ret.begin(), tmp.begin(), tmp.end());
  for (size_t i = 1; i < mac_addr::LENGTH; i++) {
    tmp = fmt::format("{:02x}:", (m_ >> i * 8) % 256);
    ret.insert(ret.begin(), tmp.begin(), tmp.end());
  }

  return ret;
}

bool mac_addr::is_mac_format(const std::vector<uint8_t> &m) {
  return m.size() == mac_addr::LENGTH;
}

bool mac_addr::is_mac_format(const std::string &m) {
  if (m.size() == mac_addr::STRING_LENGTH) {
    auto ret = m | ranges::views::remove_if(is_delimeter) |
               ranges::views::filter([](const char c) { return !isxdigit(c); });
    if (ret.empty())
      return true;
  }
  return false;
}

bool mac_addr::operator==(const mac_addr &a) const { return this->m_ == a.m_; }

bool mac_addr::operator!=(const mac_addr &a) const { return !((*this) == a); }

std::ostream &operator<<(std::ostream &os, const mac_addr &m) {
  os << m.getString();
  return os;
}
