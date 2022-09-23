cmake_minimum_required(VERSION 3.23)
project(OpenCV)

list(APPEND CMAKE_PREFIX_PATH "/home/vivallo/opencv/build")

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(OpenCV main.cpp src/Server.cpp src/Server.hpp src/controllers/ImageController.cpp src/controllers/ImageController.hpp)

target_link_libraries(OpenCV ${OpenCV_LIBS})