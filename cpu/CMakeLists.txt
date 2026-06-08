cmake_minimum_required(VERSION 3.20)
project(hpc_cpu_demos LANGUAGES CXX)

option(HPC_BUILD_CPU_ASYNC_DEMOS "Build CPU async/future/promise demos" ON)
option(HPC_BUILD_CPU_MEMORY_POOL_DEMO "Build CPU memory pool demo" ON)
option(HPC_BUILD_CPU_THREAD_POOL_DEMO "Build CPU thread pool demo" ON)
option(HPC_BUILD_CPU_MULTI_THREAD_DEMOS "Build CPU multi-thread demos" ON)
option(HPC_BUILD_CPU_SOFTWARE_OPT_DEMOS "Build CPU software optimization demos" ON)
option(HPC_BUILD_CPU_SIMD_DEMOS "Build CPU SIMD demos" OFF)

if(HPC_BUILD_CPU_ASYNC_DEMOS)
  add_subdirectory(async_sync)
endif()

if(HPC_BUILD_CPU_MEMORY_POOL_DEMO)
  add_subdirectory(memory_pool_demo)
endif()

if(HPC_BUILD_CPU_THREAD_POOL_DEMO)
  add_subdirectory(thread_pool_demo)
endif()

if(HPC_BUILD_CPU_MULTI_THREAD_DEMOS)
  add_subdirectory(multi_threads)
endif()

if(HPC_BUILD_CPU_SOFTWARE_OPT_DEMOS)
  add_subdirectory(software_optimization)
endif()

if(HPC_BUILD_CPU_SIMD_DEMOS)
  add_subdirectory(SIMD)
endif()
