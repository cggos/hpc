cmake_minimum_required(VERSION 2.8)

project(neon_demo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -mcpu=cortex-a53 -mfpu=neon-vfpv4 -mfloat-abi=softfp -ffast-math")

add_executable(neon_demo01 neon_demo01.cc)
