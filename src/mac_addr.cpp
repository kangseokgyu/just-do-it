#include "mac_addr.h"

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include <fmt/format.h>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/remove_if.hpp>

MacAddr::MacAddr() {}

MacAddr::MacAddr(const uint64_t &m) { m_ = m; }

MacAddr::MacAddr(const std::vector<uint8_t> m) {
  if (isMacFormat(m)) {
    m_ = ranges::accumulate(m, (uint64_t)0, [](uint64_t mac, const uint8_t &b) {
      return mac << 8 | b;
    });
  }
}

MacAddr::MacAddr(const std::string &m) {
  if (isMacFormat(m)) {
  }
}

bool MacAddr::isMacFormat(const std::vector<uint8_t> &m) {
  return m.size() == MacAddr::LENGTH;
}

bool MacAddr::isMacFormat(const std::string &m) {
  if (m.size() == MacAddr::STRING_LENGTH) {
    auto ret =
        m |
        ranges::views::remove_if([](char c) { return c == ':' || c == '-'; }) |
        ranges::views::filter([](const char c) { return !isxdigit(c); });
    if (ret.empty())
      return true;
  }
  return false;
}

bool MacAddr::operator==(const MacAddr &a) const { return this->m_ == a.m_; }
bool MacAddr::operator!=(const MacAddr &a) const { return !((*this) == a); }

std::ostream &operator<<(std::ostream &os, const MacAddr &m) {
  os << m.m_;
  return os;
}
