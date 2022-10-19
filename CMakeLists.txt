cmake_minimum_required(VERSION 3.23)
project(image_processing_apis)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# Open CV Configuration
list(APPEND CMAKE_PREFIX_PATH "/home/vivallo/opencv/build")
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/home/vivallo/vcpkg/installed/x64-linux/include")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/home/vivallo/vcpkg/installed/x64-linux/lib")

# OpenCV
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    message(STATUS "OpenCV found and configured")
endif()

# Boost Asio
find_package(Boost COMPONENTS log REQUIRED)
if (Boost_FOUND)
    set(ASIO_FOUND "YES")
    include_directories(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST")
    message(STATUS "Boost found and configured")
    message(STATUS "Directory" ${Boost_INCLUDE_DIR})
endif()

# Boost Log
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

add_executable(image_processing_apis main.cpp src/Server.cpp src/controllers/ImageController.cpp
        src/controllers/ImageController.hpp src/dtos/ImageDto.cpp src/dtos/ImageDto.hpp
        src/handlers/ImageHandler.cpp src/utils/Utils.cpp)

target_link_libraries(image_processing_apis
        ${OpenCV_LIBS}
        ${Boost_INCLUDE}
        Boost::boost
        Boost::log
        )