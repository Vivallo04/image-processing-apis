cmake_minimum_required(VERSION 3.23)
project(OpenCVPOC)

list(APPEND CMAKE_PREFIX_PATH "/home/vivallo/opencv/build"  )

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(OpenCVPOC main.cpp)

target_link_libraries(OpenCVPOC ${OpenCV_LIBS})