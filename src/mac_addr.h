#ifndef _JUST_DO_IT_MAC_ADDR_H_
#define _JUST_DO_IT_MAC_ADDR_H_

#include <ostream>
#include <string>
#include <vector>

class MacAddr {
private:
  uint64_t m_ = 0;

public:
  MacAddr();
  MacAddr(const uint64_t &m);
  MacAddr(const std::vector<uint8_t> m);
  MacAddr(const std::string &m);

  static bool isMacFormat(const std::vector<uint8_t> &m);
  static bool isMacFormat(const std::string &m);

  bool operator==(const MacAddr &a) const;
  bool operator!=(const MacAddr &a) const;
  friend std::ostream &operator<<(std::ostream &os, const MacAddr &m);

  constexpr static size_t LENGTH = 6;         // {0x0, 0x0, 0x0, 0x0, 0x0, 0x0}
  constexpr static size_t STRING_LENGTH = 17; // 00:00:00:00:00:00
};

#endif /* _JUST_DO_IT_MAC_ADDR_H_ */
