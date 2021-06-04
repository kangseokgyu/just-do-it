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

add_compile_options(-std=c++17 -Wall -Wextra -Wshadow)

find_package(Threads REQUIRED)

add_library(jdi)
target_sources(jdi
  PRIVATE
    event.cpp
    mac_addr.cpp
  PUBLIC
    event.h
    mac_addr.h
)
target_include_directories(jdi
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${fmt_SOURCE_DIR}/include
    ${range_SOURCE_DIR}/include
    ${zlog_SOURCE_DIR}/src
)

add_executable(just-do-it
  main.cpp
  event.cpp
  mac_addr.cpp
)
target_include_directories(just-do-it
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${range_SOURCE_DIR}/include
    ${zlog_SOURCE_DIR}/src
)
target_link_libraries(just-do-it
  PRIVATE
    Threads::Threads
    fmt
    pcap
    zlog
)
