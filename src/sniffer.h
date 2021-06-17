#ifndef _JUST_DO_IT_SNIFFER_H_
#define _JUST_DO_IT_SNIFFER_H_

#include <memory>
#include <optional>
#include <queue>
#include <string>
#include <vector>

#include "pcap.h"

enum class sniff_mode {
  unknown = 0x0,
  live = 0x1,
  offline = 0x2,
};

using packet = std::vector<uint8_t>;
using packet_ptr = std::shared_ptr<packet>;

class sniffer {
private:
  std::string name_ = "";
  sniff_mode mode_ = sniff_mode::unknown;

  pcap_t *pd_ = nullptr;

  std::queue<packet_ptr> packet_q_;

  void init_pcap();
  bool verify_radiotap_header(const struct pcap_pkthdr *h, const u_char *sp);

public:
  sniffer(std::string name, sniff_mode mode);
  ~sniffer();

  void sniff();
  std::optional<packet_ptr> fetch_packet();

  static void fetch_live(u_char *user, const struct pcap_pkthdr *h,
                         const u_char *sp);
  static void fetch_file(u_char *user, const struct pcap_pkthdr *h,
                         const u_char *sp);
};

#endif /* _JUST_DO_IT_SNIFFER_H_ */
