cmake_minimum_required(VERSION 3.18)
project(hpc_gpu_demos LANGUAGES CXX)

option(HPC_BUILD_CUDA_DEMOS "Build CUDA demos" OFF)
option(HPC_BUILD_OPENCL_DEMOS "Build OpenCL demos" OFF)

if(HPC_BUILD_CUDA_DEMOS)
  add_subdirectory(CUDA/test_cuda)
endif()

if(HPC_BUILD_OPENCL_DEMOS)
  add_subdirectory(OpenCL)
endif()
