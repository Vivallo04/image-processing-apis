cmake_minimum_required(VERSION 3.23)
project(OpenCV)

list(APPEND CMAKE_PREFIX_PATH "/home/vivallo/opencv/build")

set(CMAKE_CXX_STANDARD 20)
set(BOOST_ROOT /home/vivallo/vcpkg/installed/x64-linux/include/boost)

find_package(OpenCV REQUIRED)
find_package(GTest CONFIG REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Add VCPKG libraries
include_directories(/home/vivallo/vcpkg/installed/x64-linux/include)
link_directories(/home/vivallo/vcpkg/installed/x64-linux/lib)

add_executable(OpenCV main.cpp src/Server.cpp src/Server.hpp src/controllers/ImageController.cpp src/controllers/ImageController.hpp)

# Add Boost and Google Test
target_link_libraries(OpenCV boost PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

# this is heuristically generated, and may not be correct



target_link_libraries(OpenCV ${OpenCV_LIBS})