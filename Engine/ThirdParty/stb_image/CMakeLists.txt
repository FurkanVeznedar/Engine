cmake_minimum_required(VERSION 3.6.0)
project(Stb_image)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(stb_image
    STATIC
    ./stb_image.h
    ./stb_image.cpp)

target_include_directories(stb_image
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src)