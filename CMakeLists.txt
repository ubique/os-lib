cmake_minimum_required(VERSION 3.12.1)
project(os_lib)

set(CMAKE_CXX_STANDARD 14)

include_directories(static-lib)
include_directories(first-dynamic-lib)
include_directories(second-dynamic-lib)

add_subdirectory(static-lib)
add_subdirectory(first-dynamic-lib)
add_subdirectory(second-dynamic-lib)

add_executable(os_lib main.cpp)

target_link_libraries(os_lib static-lib)
target_link_libraries(os_lib first-dynamic-lib)
target_link_libraries(os_lib -ldl)