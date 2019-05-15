cmake_minimum_required(VERSION 3.0)
project(os_lib)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(libs)
add_executable(os_lib main.cpp)
target_link_libraries(os_lib static dyn1 -ldl)