cmake_minimum_required(VERSION 2.8)

project(sse_demo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -msse2")

add_executable(sse_demo01 sse_demo01.cpp)

add_executable(sse_demo02 sse_demo02.cpp)

add_executable(sse_demo03 sse_demo03.cpp)
