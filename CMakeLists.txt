cmake_minimum_required(VERSION 3.23)
project(OpenCV)

list(APPEND CMAKE_PREFIX_PATH "/home/vivallo/opencv/build")

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(OpenCV main.cpp src/Server.cpp src/Server.hpp src/controllers/ImageController.cpp src/controllers/ImageController.hpp test/ImageControllerTest.cpp test/main.cpp)

target_link_libraries(OpenCV ${OpenCV_LIBS})