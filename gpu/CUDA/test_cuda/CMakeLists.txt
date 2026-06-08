cmake_minimum_required(VERSION 3.18)
project(hpc_cuda_demo LANGUAGES CXX)

if(NOT CMAKE_CUDA_ARCHITECTURES)
  set(CMAKE_CUDA_ARCHITECTURES 52)
endif()

if(NOT CMAKE_CUDA_COMPILER)
  find_program(CMAKE_CUDA_COMPILER nvcc HINTS /usr/local/cuda/bin)
endif()

enable_language(CUDA)

add_executable(hpc_cuda_test test.cu)
target_compile_features(hpc_cuda_test PRIVATE cxx_std_17)
set_target_properties(hpc_cuda_test PROPERTIES
  CUDA_STANDARD 17
  CUDA_STANDARD_REQUIRED ON
  OUTPUT_NAME test_cuda)
