cmake_minimum_required(VERSION 3.8)

project(oslib)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(libs)

add_executable(libs_test main.cpp)

target_link_libraries(libs_test static_lb dyn1_lb dl)
