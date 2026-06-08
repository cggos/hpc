cmake_minimum_required(VERSION 3.20)
project(shared_memory_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)
find_library(HPC_RT_LIBRARY rt)

add_library(hpc_shared_memory_demo_lib ../../src/cpu/shared_memory.cpp)
target_include_directories(hpc_shared_memory_demo_lib PUBLIC ../../include)
target_link_libraries(hpc_shared_memory_demo_lib PUBLIC Threads::Threads)
if(HPC_RT_LIBRARY)
  target_link_libraries(hpc_shared_memory_demo_lib PUBLIC ${HPC_RT_LIBRARY})
endif()

add_executable(shared_memory_demo shared_memory_demo.cpp)
target_link_libraries(shared_memory_demo PRIVATE hpc_shared_memory_demo_lib)
