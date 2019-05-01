cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 14)

project(os-lib)
add_executable(${PROJECT_NAME} "main.cpp")

add_library(static-lib STATIC static.cpp)
add_library(first-dynamic-lib SHARED first-dynamic.cpp)
add_library(second-dynamic-lib SHARED second-dynamic.cpp)

target_link_libraries(${PROJECT_NAME} static-lib first-dynamic-lib dl)
