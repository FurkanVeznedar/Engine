cmake_minimum_required(VERSION 3.6.0)
project(glfw)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(glfw_files
    ./include/GLFW/glfw3.h
    ./include/GLFW/glfw3native.h
    ./src/internal.h
    ./src/platform.h
    ./src/mappings.h
    ./src/context.c
    ./src/init.c
    ./src/input.c
    ./src/monitor.c
    ./src/platform.c
    ./src/vulkan.c
    ./src/window.c
    ./src/egl_context.c
    ./src/osmesa_context.c
    ./src/null_platform.h
    ./src/null_joystick.h
    ./src/null_init.c
    
    ./src/null_monitor.c
    ./src/null_window.c
    ./src/null_joystick.c)

if(WIN32)
    list(APPEND glfw_files
        ./src/win32_init.c
        ./src/win32_module.c
        ./src/win32_joystick.c
        ./src/win32_monitor.c
        ./src/win32_time.h
        ./src/win32_time.c
        ./src/win32_thread.h
        ./src/win32_thread.c
        ./src/win32_window.c
        ./src/wgl_context.c
        ./src/egl_context.c
        ./src/osmesa_context.c)
endif(WIN32)

add_library(glfw
    STATIC
    ${glfw_files})

if(WIN32)
    target_compile_definitions(glfw
        PRIVATE
        _GLFW_WIN32
        _CRT_SECURE_NO_WARNINGS)
endif(WIN32)

target_include_directories(glfw
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../glfw)