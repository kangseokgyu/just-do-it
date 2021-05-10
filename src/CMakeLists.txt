add_compile_options(-std=c++14 -Wall -Wextra -Wshadow)

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
)

add_executable(just-do-it
  main.cpp
  event.cpp
)
target_include_directories(just-do-it PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(just-do-it PRIVATE Threads::Threads)
