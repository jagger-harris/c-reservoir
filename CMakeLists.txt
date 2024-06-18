# Project definitions
cmake_minimum_required(VERSION 3.5)
project(reservoir C)

# Project options
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-std=c89 -Wall -Wpedantic -fsanitize=address")

# Get all sources
file(GLOB_RECURSE HEADER_FILES src/*.h)
file(GLOB_RECURSE SOURCE_FILES src/*.c)

# Add subdirectory for tests
add_subdirectory(tests)
