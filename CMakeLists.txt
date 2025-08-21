cmake_minimum_required(VERSION 3.28)
project(hpc)

message("\n******************************** project hpc ********************************")

set(HPC_VERSION_MAJOR 1)
set(HPC_VERSION_MINOR 0)
set(HPC_VERSION_PATCH 0)

option(HPC_BUILD_TEST "Build unit tests" OFF)

include(${PROJECT_SOURCE_DIR}/cmake/build_flags.cmake)

set(Eigen3_DIR "$ENV{CG_THIRDPARTY}/${PLATFORM_ARCH}/eigen3/share/eigen3/cmake/")
find_package(Eigen3 REQUIRED)

set(OpenCV_DIR "$ENV{CG_THIRDPARTY}/${PLATFORM_ARCH}/opencv/lib/cmake/opencv4/")
find_package(OpenCV 4.2 REQUIRED COMPONENTS core)
set(OpenCV_INCLUDE_DIRS "$ENV{CG_THIRDPARTY}/${PLATFORM_ARCH}/opencv/include/opencv4/")

include_directories(include)

# ******************************** common ********************************
add_library(${PROJECT_NAME}.common SHARED src/common/print.cpp)
target_link_libraries(${PROJECT_NAME}.common pthread)

# ******************************** hpc ********************************
add_library(${PROJECT_NAME} SHARED src/cpu/cpu.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${HPC_VERSION_MAJOR}.${HPC_VERSION_MINOR}.${HPC_VERSION_PATCH} SOVERSION ${HPC_VERSION_MAJOR})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

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

# ******************************** install ********************************
install(DIRECTORY include/${PROJECT_NAME} DESTINATION include PATTERN ".cc" EXCLUDE)

install(TARGETS ${PROJECT_NAME}.common ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

