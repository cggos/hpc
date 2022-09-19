cmake_minimum_required(VERSION 2.8)

project(sse_msvc)

add_executable(${CMAKE_PROJECT_NAME} main.cpp CpuInfo.cpp Timer.cxx)
