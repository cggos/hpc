cmake_minimum_required(VERSION 3.20)
project(memory_pool_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(memory_pool_demo memory_pool_demo.cpp ../../src/cpu/memory_pool.cpp)
target_include_directories(memory_pool_demo PRIVATE ../../include)
