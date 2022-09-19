cmake_minimum_required( VERSION 2.8 )

project( test_cuda )

find_package( CUDA REQUIRED )

set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS} -O3 -gencode arch=compute_52,code=sm_52 --std=c++11)

cuda_add_executable(${PROJECT_NAME} test.cu)
target_link_libraries(${PROJECT_NAME} ${CUDA_LIBRARIES})
