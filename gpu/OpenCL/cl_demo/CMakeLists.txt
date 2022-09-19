cmake_minimum_required(VERSION 2.8)
project(cl_demo)

add_executable(demo01 demo01.cpp)
target_link_libraries(demo01 OpenCL)

add_executable(demo02 demo02.cpp)
target_link_libraries(demo02 OpenCL)
