cmake_minimum_required(VERSION 3.23)
project(image_processing_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
enable_testing()

# Open CV
list(APPEND CMAKE_PREFIX_PATH "/home/vivallo/opencv/build")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Google Test
add_subdirectory(../lib/googletest ../src/controllers)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

add_executable(image_processing_test main.cpp ImageControllerTest.cpp)

target_link_libraries(image_processing_test
        ${OpenCV_LIBS}
        gtest
        gtest_main
        gmock_main)


