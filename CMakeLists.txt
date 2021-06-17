cmake_minimum_required(VERSION 3.13.0)

project(just-do-it)
include(CTest)

include(FetchContent)
FetchContent_Declare(range
  GIT_REPOSITORY https://github.com/ericniebler/range-v3
  GIT_TAG        0.11.0
)

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        7.1.3
)

FetchContent_Declare(pcap
  GIT_REPOSITORY https://github.com/the-tcpdump-group/libpcap.git
  GIT_TAG        libpcap-1.10
)

FetchContent_Declare(zlog
  GIT_REPOSITORY https://github.com/lisongmin/zlog.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(range fmt pcap zlog)

add_subdirectory(src)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()
