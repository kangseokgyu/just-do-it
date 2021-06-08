cmake_minimum_required(VERSION 3.13.0)

project(just-do-it)
include(CTest)

add_subdirectory(src)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()
