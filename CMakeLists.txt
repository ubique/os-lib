cmake_minimum_required(VERSION 3.5.1)

project(os-lib)

set(CMAKE_CXX_STANDARD 14)

add_library(hello STATIC hello.cpp)
add_library(pow1 SHARED pow1.cpp)
add_library(pow2 SHARED pow2.cpp)

add_executable(os-lib "main.cpp")

target_link_libraries(os-lib hello pow1 -ldl)