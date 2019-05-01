cmake_minimum_required(VERSION 3.10)
project(task4)

set(CMAKE_CXX_STANDARD 14)

add_executable(task4 main.cpp)

add_library(and_static STATIC and_static.cpp and_static.h)
add_library(or_dynamic SHARED or_dynamic.cpp or_dynamic.h)
add_library(xor_loaded SHARED xor_loaded.cpp xor_loaded.h)

target_link_libraries(task4 and_static)
target_link_libraries(task4 or_dynamic)
target_link_libraries(task4 ${CMAKE_DL_LIBS})
