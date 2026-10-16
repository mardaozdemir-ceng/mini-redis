cmake_minimum_required(VERSION 3.15)
project(MiniRedis VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# 1. MAIN DATA PROGRAM
add_library(kvstore_lib
    src/kvstore.cpp
)

# 2. INTERACTIVE CLI PROGRAM
add_executable(mini_redis
    src/main.cpp
)
target_link_libraries(mini_redis PRIVATE kvstore_lib)

# -------------------------------------------------------------
# 3. GOOGLETEST INTEGRATION
# -------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# FOR WINDOWS
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Our separate program that will run the tests.
add_executable(kvstore_tests
    tests/test_kvstore.cpp
)
# We link our engine and GoogleTest’s provided main() function to the test program.
target_link_libraries(kvstore_tests PRIVATE kvstore_lib gtest_main)

#include(GoogleTest)
#gtest_discover_tests(run_tests)