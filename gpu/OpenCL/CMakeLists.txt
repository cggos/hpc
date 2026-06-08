cmake_minimum_required(VERSION 3.10)
project(hpc_opencl_demos LANGUAGES CXX)

option(HPC_BUILD_OPENCL_BASIC_DEMOS "Build basic OpenCL demos" ON)
option(HPC_BUILD_OPENCL_OPENCV_DEMOS "Build OpenCV OpenCL demos" OFF)

if(HPC_BUILD_OPENCL_BASIC_DEMOS)
  add_subdirectory(cl_demo)
endif()

if(HPC_BUILD_OPENCL_OPENCV_DEMOS)
  add_subdirectory(opencv_cl)
endif()
