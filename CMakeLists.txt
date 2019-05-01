cmake_minimum_required(VERSION 3.0)
project(OS_lib)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG -fsanitize=address,undefined")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_library(inc STATIC inc.h inc.cpp)
add_library(mul SHARED mul.h mul.cpp)
add_library(sum SHARED sum.h sum.cpp)

add_executable(main main.cpp)

TARGET_LINK_LIBRARIES(main -ldl static mul)