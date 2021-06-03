#ifndef _JUST_DO_IT_MAC_ADDR_H_
#define _JUST_DO_IT_MAC_ADDR_H_

#include <ostream>
#include <string>
#include <vector>

class mac_addr {
private:
  uint64_t m_ = 0;

public:
  mac_addr();
  mac_addr(const uint64_t &m);
  mac_addr(const std::vector<uint8_t> m);
  mac_addr(const std::string &m);
  uint64_t get() const;
  std::string getString() const;

  static bool is_mac_format(const std::vector<uint8_t> &m);
  static bool is_mac_format(const std::string &m);

  bool operator==(const mac_addr &a) const;
  bool operator!=(const mac_addr &a) const;
  friend std::ostream &operator<<(std::ostream &os, const mac_addr &m);

  constexpr static size_t LENGTH = 6;         // {0x0, 0x0, 0x0, 0x0, 0x0, 0x0}
  constexpr static size_t STRING_LENGTH = 17; // 00:00:00:00:00:00
  constexpr static uint64_t BROADCAST_MAC = 0xff'ff'ff'ff'ff'ff;
};

#endif /* _JUST_DO_IT_MAC_ADDR_H_ */
