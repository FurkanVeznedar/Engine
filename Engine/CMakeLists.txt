cmake_minimum_required(VERSION 3.6.0)
project(App)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glad)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glfw)

set(ENGINE_SOURCES
    src/Engine/Application.cpp
    src/Engine/Log.cpp
    src/Platform/WindowsWindow.cpp
    src/Engine/Layer.cpp
    src/Engine/LayerStack.cpp
    src/Engine/ImGui/ImGuiLayer.cpp
    src/Engine/ImGui/ImGuiBuild.cpp
    src/Platform/WindowsInput.cpp
    src/Platform/OpenGL/OpenGLContext.cpp
    src/Engine/Renderer/Shader.cpp
    src/Engine/Renderer/Buffer.cpp
    src/Engine/Renderer/Renderer.cpp
    src/Platform/OpenGL/OpenGLBuffer.cpp
    src/Engine/Renderer/VertexArray.cpp
    src/Platform/OpenGL/OpenGLVertexArray.cpp
    src/Engine/Renderer/RendererAPI.cpp
    src/Engine/Renderer/RenderCommand.cpp
    src/Platform/OpenGL/OpenGLRendererAPI.cpp
    src/Engine/Renderer/Camera.cpp)

add_library(Engine_lib
    STATIC
    ${ENGINE_SOURCES})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Engine_lib PRIVATE EN_DEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(Engine_lib PRIVATE EN_RELEASE)
endif()

target_include_directories(Engine_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/ThirdParty/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/ThirdParty/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/ThirdParty/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/ThirdParty/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/ThirdParty/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/ThirdParty/glfw/include)

target_link_libraries(Engine_lib
    PRIVATE
    glad
    glfw
    imgui)

target_compile_definitions(Engine_lib
    PRIVATE
    EN_ENABLE_ASSERTS
    GLFW_INCLUDE_NONE
    _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)