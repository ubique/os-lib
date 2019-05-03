cmake_minimum_required(VERSION 3.1)
project(lib)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG -fsanitize=address,undefined")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_library(static STATIC snake.h field_sizes.cpp)
add_library(shared SHARED snake_logic.cpp)
add_library(second_shared SHARED printer.cpp)

add_executable(snake main.cpp)

TARGET_LINK_LIBRARIES(snake -ldl static shared)
