include(FetchContent)
FetchContent_Declare(range
  GIT_REPOSITORY https://github.com/ericniebler/range-v3
  GIT_TAG        0.11.0
)
FetchContent_MakeAvailable(range)

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        7.1.3
)
FetchContent_MakeAvailable(fmt)

add_compile_options(-std=c++17 -Wall -Wextra -Wshadow)

find_package(Threads REQUIRED)

add_library(jdi)
target_sources(jdi
  PRIVATE
    event.cpp
  PUBLIC
    event.h
)
target_include_directories(jdi
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${fmt_SOURCE_DIR}/include
    ${range_SOURCE_DIR}/include
)

add_executable(just-do-it
  main.cpp
  event.cpp
)
target_include_directories(just-do-it
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${range_SOURCE_DIR}/include
)
target_link_libraries(just-do-it
  PRIVATE
    Threads::Threads
    fmt
)