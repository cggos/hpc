cmake_minimum_required(VERSION 3.10)
project(hpc_cpu_software_optimization_demos LANGUAGES CXX)

find_package(Threads REQUIRED)

add_executable(hpc_bind_cpu bind_cpu.cpp)
target_compile_features(hpc_bind_cpu PRIVATE cxx_std_17)
target_link_libraries(hpc_bind_cpu PRIVATE Threads::Threads)
set_target_properties(hpc_bind_cpu PROPERTIES OUTPUT_NAME bind_cpu)

add_executable(hpc_test_cpu_cache test_cpu_cache.cpp)
target_compile_features(hpc_test_cpu_cache PRIVATE cxx_std_17)
set_target_properties(hpc_test_cpu_cache PROPERTIES OUTPUT_NAME test_cpu_cache)
