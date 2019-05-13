cmake_minimum_required(VERSION 2.8)

project(os-lib)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG ")

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(static_lib)
add_subdirectory(shared_lib1)
add_subdirectory(shared_lib2)

include_directories(static_lib)
include_directories(shared_lib1)
include_directories(shared_lib2)

add_executable(os-lib main.cpp)

target_link_libraries(os-lib static_lib)
target_link_libraries(os-lib shared_lib1)
target_link_libraries(os-lib -ldl)

