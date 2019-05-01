cmake_minimum_required(VERSION 3.10)
project(libs)


add_library(static STATIC static.cpp)
add_library(first_dynamic  SHARED first_dynamic.cpp)
add_library(second_dynamic SHARED second_dynamic.cpp)

add_executable(libs main.cpp)

target_link_libraries(libs static first_dynamic -ldl)
