cmake_minimum_required(VERSION 3.10)
project(hpc_cpu_async_demos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

function(add_hpc_async_demo target output source)
  add_executable(${target} ${source})
  target_compile_features(${target} PRIVATE cxx_std_17)
  target_link_libraries(${target} PRIVATE Threads::Threads)
  set_target_properties(${target} PROPERTIES OUTPUT_NAME ${output})
endfunction()

add_hpc_async_demo(hpc_async00 async00 async_00.cpp)
add_hpc_async_demo(hpc_async01 async01 async_01.cpp)
add_hpc_async_demo(hpc_async02 async02 async_02.cpp)
add_hpc_async_demo(hpc_promise00 promise00 promise_00.cpp)
add_hpc_async_demo(hpc_packaged_task00 packaged_task00 packaged_task_00.cpp)
add_hpc_async_demo(hpc_async_demo async_demo demo.cpp)
