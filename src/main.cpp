#include <unistd.h>

#include <chrono>
#include <iostream>
#include <list>
#include <memory>
#include <thread>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include "fmt/format.h"
#include "range/v3/all.hpp"

#include "mac_addr.h"
#include "sniffer.h"

using namespace std::chrono;

int main(int argc, char **argv) {
  std::list<std::string> ifs;
  std::list<std::string> files;
  int c = 0;

  while ((c = getopt(argc, argv, "i:f:")) != EOF) {
    switch (c) {
    case 'i':
      ifs.push_back(optarg);
      break;

    case 'f':
      files.push_back(optarg);
      break;
    }
  }

  std::cout << "interfaces: " << ranges::views::all(ifs) << '\n';
  std::cout << "files: " << ranges::views::all(files) << '\n';

  std::list<sniffer> sniffers;
  for (auto name : ifs) {
    sniffers.push_back(sniffer(name, sniff_mode::live));
  }
  for (auto name : files) {
    sniffers.push_back(sniffer(name, sniff_mode::offline));
  }

  std::list<std::thread> ts;
  for (auto &s : sniffers) {
    ts.push_back(std::thread(&sniffer::sniff, std::ref(s)));
  }

  for (auto &t : ts) {
    t.join();
  }

  for (auto &s : sniffers) {
    int i = 0;
    while (true) {
      auto op = s.fetch_packet();
      if (op) {
        fmt::print("-- {}\n", i);
        for (auto p : **op) {
          fmt::print("{:02x} ", p);
        }
        i++;
        fmt::print("\n");
      } else {
        break;
      }
    }
  }

  return 0;
}
