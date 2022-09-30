cmake_minimum_required(VERSION 3.23)
project(OpenCV)

list(APPEND CMAKE_PREFIX_PATH "/home/vivallo/opencv/build")

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")

enable_testing()

add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})



add_executable(OpenCV test/ImageControllerTest.cpp test/main.cpp)

target_link_libraries(OpenCV ${OpenCV_LIBS}
        gtest
        gtest_main
        gmock_main)