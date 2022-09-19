cmake_minimum_required( VERSION 2.8 )
project( test_opencv_cl )

set( CMAKE_CXX_FLAGS "-std=c++11" )

find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui calib3d)
if (OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    link_libraries(${OpenCV_LIBS})
endif ()

add_executable( camera camera.cc )
target_link_libraries( camera ${OpenCV_LIBS} )

add_executable( stereobm stereobm.cc )
target_link_libraries( stereobm ${OpenCV_LIBS} )

add_executable(test_ocl test_ocl.cpp)
