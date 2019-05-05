cmake_minimum_required(VERSION 3.12.1)
project(os_lib)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tmp)

add_library(st STATIC st.h st.cpp)
add_library(dyn1 SHARED dyn1.h dyn1.cpp)
add_library(dyn2 SHARED dyn2.h dyn2.cpp)
add_executable(os_lib main.cpp)
target_link_libraries(os_lib -ldl st dyn1)
