cmake_minimum_required(VERSION 3.10)
project(hpc_opencl_basic_demos LANGUAGES CXX)

find_package(OpenCL REQUIRED)

add_executable(hpc_opencl_info demo01.cpp)
target_compile_features(hpc_opencl_info PRIVATE cxx_std_17)
target_link_libraries(hpc_opencl_info PRIVATE OpenCL::OpenCL)
set_target_properties(hpc_opencl_info PROPERTIES OUTPUT_NAME opencl_info)

add_executable(hpc_opencl_vecadd demo02.cpp)
target_compile_features(hpc_opencl_vecadd PRIVATE cxx_std_17)
target_link_libraries(hpc_opencl_vecadd PRIVATE OpenCL::OpenCL)
set_target_properties(hpc_opencl_vecadd PROPERTIES OUTPUT_NAME opencl_vecadd)
