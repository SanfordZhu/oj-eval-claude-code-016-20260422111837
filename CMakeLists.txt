cmake_minimum_required(VERSION 3.10)
project(problem_016)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(code src/main.cpp src/bpt.hpp)

# Optimize for speed
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(code PRIVATE -O2 -pipe -march=native)
endif()
