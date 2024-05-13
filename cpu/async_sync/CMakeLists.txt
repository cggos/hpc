cmake_minimum_required(VERSION 3.10)
project(async_sync)

set(CMAKE_CXX_STANDARD 17)

add_executable(async00 async_00.cpp)
add_executable(async01 async_01.cpp)
add_executable(async02 async_02.cpp)

add_executable(promise00 promise_00.cpp)

add_executable(packaged_task00 packaged_task_00.cpp)

add_executable(demo demo.cpp)
