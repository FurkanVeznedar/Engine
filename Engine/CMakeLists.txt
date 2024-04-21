cmake_minimum_required(VERSION 3.6.0)
project(App)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)



set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/GLAD)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui)

set(ENGINE_SOURCES
    src/Engine/Application.cpp
    src/Engine/Log.cpp
    src/Platform/WindowsWindow.cpp
    src/Engine/Layer.cpp
    src/Engine/LayerStack.cpp
    src/Engine/ImGui/ImGuiLayer.cpp
    src/Platform/OpenGL/ImGuiOpenGLRenderer.cpp
    src/Platform/WindowsInput.cpp)

add_library(Engine_lib
    SHARED
    ${ENGINE_SOURCES})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Engine_lib PRIVATE EN_DEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(Engine_lib PRIVATE EN_RELEASE)
endif()

target_precompile_headers(Engine_lib
    PRIVATE
    src/Enpch.h)

target_include_directories(Engine_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/ThirdParty/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/ThirdParty/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/ThirdParty/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/ThirdParty/GLAD/include)

target_link_libraries(Engine_lib
    PRIVATE
    glad
    imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/Dependencies/GLFW/glfw3dll.lib
    opengl32.lib)

target_compile_definitions(Engine_lib
    PRIVATE
    EN_PLATFORM_WINDOWS
    EN_BUILD_DLL
    GLFW_DLL
    GLFW_INCLUDE_NONE)