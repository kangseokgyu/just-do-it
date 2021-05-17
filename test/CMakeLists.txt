include(FetchContent)
FetchContent_Declare(gtest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)

FetchContent_MakeAvailable(gtest)

add_executable(unit_test
  mac_addr_test.cpp
)

target_include_directories(unit_test
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

target_link_libraries(unit_test
  PRIVATE
    jdi
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_test
  PROPERTIES
    LABELS "unit"
  DISCOVER_TIMEOUT
    240
)
