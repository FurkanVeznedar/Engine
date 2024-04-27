cmake_minimum_required(VERSION 3.6.0)
project(App)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(Engine)

add_executable(${PROJECT_NAME}
    ./src/App.cpp)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    EN_PLATFORM_WINDOWS
    _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Engine_lib)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/Engine/src)