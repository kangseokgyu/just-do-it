#include "sniffer.h"

#include "fmt/format.h"
#include "pcap.h"
#include "poll.h"

sniffer::sniffer(std::string name, sniff_mode mode) {
  name_ = name;
  mode_ = mode;

  init_pcap();
}

void sniffer::init_pcap() {
  char ebuf[PCAP_ERRBUF_SIZE] = {0};

  if (mode_ == sniff_mode::live) {
    pd_ = pcap_open_live(name_.c_str(), 65535, 0, 1000, ebuf);
  } else if (mode_ == sniff_mode::offline) {
    pd_ = pcap_open_offline(name_.c_str(), ebuf);
  }

  if (pd_ == nullptr || *ebuf) {
    fmt::print("{}\n", ebuf);
    exit(1);
  }
}

void sniffer::sniff() {
  if (mode_ == sniff_mode::live) {
    int selectable_fd = pcap_get_selectable_fd(pd_);
    while (true) {
      struct pollfd fd = {};
      fd.fd = selectable_fd;
      fd.events = POLLIN;

      int status = poll(&fd, 1, -1);
      if (status != -1) {
        // status = pcap_dispatch(pd_, -1, &sniffer::);

        if (status < 0)
          break;
      }
    }
  } else if (mode_ == sniff_mode::offline) {
    fmt::print("[{}] Start sniffing. [mode: offline]\n", name_);
    if (pcap_loop(pd_, 0, &sniffer::fetch_file, (u_char *)this) < 0) {
      fmt::print("error: pcap_loop\n");
      exit(1);
    }
    fmt::print("[{}] Finish sniffing. [mode: offline]\n", name_);
  }
}

void sniffer::fetch_file(u_char *user, const struct pcap_pkthdr *h,
                         const u_char *sp) {
  // sniffer *s = reinterpret_cast<sniffer *>(user);

  for (uint32_t i = 0; i < h->len; i++) {
    if (i % 8 == 0) {
      fmt::print(" ");
    }
    if (i % 16 == 0) {
      fmt::print("\n-- ");
    }
    fmt::print("{:02x} ", sp[i]);
  }
  fmt::print("\n");
}
