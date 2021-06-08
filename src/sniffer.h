#ifndef _JUST_DO_IT_SNIFFER_H_
#define _JUST_DO_IT_SNIFFER_H_

#include <string>

#include "pcap.h"

enum class sniff_mode {
  unknown = 0x0,
  live = 0x1,
  offline = 0x2,
};

class sniffer {
private:
  std::string name_ = "";
  sniff_mode mode_ = sniff_mode::unknown;

  pcap_t *pd_ = nullptr;

  void init_pcap();

public:
  sniffer(std::string name, sniff_mode mode);

  void sniff();

  static void fetch_file(u_char *user, const struct pcap_pkthdr *h,
                         const u_char *sp);
};

#endif /* _JUST_DO_IT_SNIFFER_H_ */
