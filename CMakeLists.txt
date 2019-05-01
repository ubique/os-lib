cmake_minimum_required(VERSION 2.8)
project(OS_lib)

set(CMAKE_CXX_STANDARD 11)

add_library(inc STATIC inc.h inc.cpp)
add_library(mul SHARED mul.h mul.cpp)
add_library(sum SHARED sum.h sum.cpp)

add_executable(main main.cpp)

TARGET_LINK_LIBRARIES(main -ldl inc mul)