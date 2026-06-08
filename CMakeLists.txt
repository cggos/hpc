cmake_minimum_required(VERSION 3.28)
project(hpc VERSION 1.0.0 LANGUAGES CXX)

message("\n******************************** project hpc ********************************")

set(HPC_VERSION_MAJOR 1)
set(HPC_VERSION_MINOR 0)
set(HPC_VERSION_PATCH 0)

option(HPC_BUILD_TEST "Build unit tests" OFF)
option(HPC_BUILD_DEMOS "Build standalone demo programs" OFF)

include(${PROJECT_SOURCE_DIR}/cmake/build_flags.cmake)

find_package(Threads REQUIRED)

set(Eigen3_DIR "$ENV{CG_APP_RELEASE}/${PLATFORM_ARCH}/eigen3/share/eigen3/cmake/")
find_package(Eigen3 REQUIRED)

set(OpenCV_DIR "$ENV{CG_APP_RELEASE}/${PLATFORM_ARCH}/opencv/lib/cmake/opencv4/")
find_package(OpenCV 4.2 REQUIRED COMPONENTS core)
set(OpenCV_INCLUDE_DIRS "$ENV{CG_APP_RELEASE}/${PLATFORM_ARCH}/opencv/include/opencv4/")

# ******************************** common ********************************
add_library(${PROJECT_NAME}.common SHARED src/common/print.cpp)
target_include_directories(${PROJECT_NAME}.common PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(${PROJECT_NAME}.common PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_NAME}.common PUBLIC Threads::Threads)

# ******************************** hpc ********************************
add_library(${PROJECT_NAME} SHARED
  src/cpu/cpu.cpp
  src/cpu/memory_pool.cpp
  src/cpu/thread_pool.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${HPC_VERSION_MAJOR}.${HPC_VERSION_MINOR}.${HPC_VERSION_PATCH} SOVERSION ${HPC_VERSION_MAJOR})
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  ${OpenCV_INCLUDE_DIRS}
  $<INSTALL_INTERFACE:include>)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBS} Threads::Threads)

# ******************************** unit test ********************************
if(HPC_BUILD_TEST)
  enable_testing()
  find_package(GTest)

  if(GTest_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_subdirectory(test)
  endif()

  install(DIRECTORY data DESTINATION .)
endif()

# ******************************** demos ********************************
if(HPC_BUILD_DEMOS)
  add_subdirectory(cpu)
  add_subdirectory(gpu)
endif()

# ******************************** install ********************************
install(DIRECTORY include/${PROJECT_NAME} DESTINATION include PATTERN ".cc" EXCLUDE)

install(TARGETS ${PROJECT_NAME}.common ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
