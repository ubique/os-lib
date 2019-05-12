cmake_minimum_required(VERSION 3.11)
project(lib)

set(CMAKE_CXX_STANDARD 14)

add_library(birb STATIC birb.cpp)
add_library(bee SHARED bee.cpp)
add_library(flower SHARED flower.cpp)

add_executable(lib main.cpp)

target_link_libraries(lib birb bee -ldl)
