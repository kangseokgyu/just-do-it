project(jdi)

add_compile_options(-std=c++17 -Wall -Wextra -Wshadow)

find_package(Threads REQUIRED)

add_library(jdi OBJECT)
target_sources(jdi
  PRIVATE
    event.cpp
    mac_addr.cpp
    sniffer.cpp
  PUBLIC
    event.h
    mac_addr.h
    sniffer.h
)
target_include_directories(jdi
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${fmt_SOURCE_DIR}/include
    ${range_SOURCE_DIR}/include
    ${zlog_SOURCE_DIR}/src
    ${pcap_SOURCE_DIR}
)
target_link_libraries(jdi
  PRIVATE
    pcap
)

add_executable(just-do-it
  main.cpp
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
    jdi
)
