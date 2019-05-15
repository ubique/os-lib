cmake_minimum_required(VERSION 3.10)
project(os-lib)

set(CMAKE_CXX_STANDARD 14)

add_library(avg_static STATIC avg_static.cpp)
add_library(min_dll SHARED min_dll.cpp)
add_library(max_dll SHARED max_dll.cpp)

add_executable(os-lib main.cpp)

target_link_libraries(os-lib avg_static min_dll -ldl)