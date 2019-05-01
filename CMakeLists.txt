cmake_minimum_required(VERSION 3.10)

project(os-lib)

set(CMAKE_CXX_STANDARD 14)

add_library(app STATIC static/Application.cpp)
add_library(interface SHARED dynamic/Interface.cpp)

add_executable(os-lib main.cpp)

target_link_libraries(os-lib app interface -ldl)