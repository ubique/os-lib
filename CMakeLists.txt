cmake_minimum_required(VERSION 3.9)

project(os-lib)

set(CMAKE_CXX_STANDARD 14)

add_library(hello STATIC hello.cpp)
add_library(module SHARED module.cpp)
add_library(pow SHARED pow.cpp)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} hello module -ldl)
