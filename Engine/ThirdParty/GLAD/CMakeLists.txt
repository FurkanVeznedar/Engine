cmake_minimum_required(VERSION 3.6.0)
project(Glad)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(glad
    STATIC
    ./include/glad/glad.h
    ./include/KHR/khrplatform.h
    ./src/glad.c)

target_include_directories(glad
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../glad/include)

