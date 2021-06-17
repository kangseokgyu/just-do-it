#include "sniffer.h"

#include "fmt/format.h"
#include "pcap.h"
#include "poll.h"

struct ieee80211_radiotap_header {
  /**
   * @it_version: radiotap version, always 0
   */
  uint8_t it_version;

  /**
   * @it_pad: padding (or alignment)
   */
  uint8_t it_pad;

  /**
   * @it_len: overall radiotap header length
   */
  uint16_t it_len;

  /**
   * @it_present: (first) present word
   */
  uint32_t it_present;
} __attribute__((__packed__));

sniffer::sniffer(std::string name, sniff_mode mode) {
  name_ = name;
  mode_ = mode;

  init_pcap();
}

sniffer::~sniffer() {}

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

bool sniffer::verify_radiotap_header(const struct pcap_pkthdr *h,
                                     const u_char *sp) {
  const ieee80211_radiotap_header *hdr =
      reinterpret_cast<const ieee80211_radiotap_header *>(sp);
  fmt::print("capture len: {:4d}, hdr len: {:2d}\n", h->len, hdr->it_len);

  if (h->len < hdr->it_len) {
    return false;
  }
  if (hdr->it_version != 0) {
    return false;
  }
  return true;
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
        status = pcap_dispatch(pd_, -1, &sniffer::fetch_live, (u_char *)this);

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

std::optional<packet_ptr> sniffer::fetch_packet() {
  if (packet_q_.empty())
    return std::nullopt;

  auto p = std::move(packet_q_.front());
  packet_q_.pop();
  return std::make_optional(p);
}

void sniffer::fetch_live(u_char *user, const struct pcap_pkthdr *h,
                         const u_char *sp) {
  sniffer *s = reinterpret_cast<sniffer *>(user);
  if (s->verify_radiotap_header(h, sp) == false) {
    exit(1);
  }

  s->packet_q_.push(std::make_shared<packet>(packet(sp, sp + h->len)));
}

void sniffer::fetch_file(u_char *user, const struct pcap_pkthdr *h,
                         const u_char *sp) {
  sniffer *s = reinterpret_cast<sniffer *>(user);
  if (s->verify_radiotap_header(h, sp) == false) {
    exit(1);
  }

  s->packet_q_.push(std::make_shared<packet>(packet(sp, sp + h->len)));
}
