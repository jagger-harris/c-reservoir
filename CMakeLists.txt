# Project definitions
cmake_minimum_required(VERSION 3.0)
project(reservoir C)

# Project options
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-std=c99 -Wall -pedantic")

# Get all sources
file(GLOB_RECURSE SOURCE_FILES tests/*.c)

add_executable(rsv_test ${SOURCE_FILES})

# CTest
add_test(NAME AllTests COMMAND rsv_test)
set_tests_properties(AllTests PROPERTIES FAIL_REGULAR_EXPRESSION "failed")
enable_testing()
