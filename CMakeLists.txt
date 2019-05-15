cmake_minimum_required(VERSION 3.10)
project(os_lib)

set(CMAKE_CXX_STANDARD 14)


add_library(static STATIC static.cpp)
add_library(dynamic SHARED dynamic.cpp)
add_library(dynlink SHARED dynlink.cpp)

add_executable(os_lib main.cpp)

target_link_libraries(os_lib static dynamic -ldl)