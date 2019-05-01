cmake_minimum_required(VERSION 3.10)
project(os_lib)

set(CMAKE_CXX_STANDARD 17)

add_library(test_static STATIC test_static.h test_static.cpp)

add_library(test_dynamic SHARED test_dynamic.h test_dynamic.cpp)

add_library(huffman SHARED huffman.h huffman.cpp)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} test_static test_dynamic -ldl)