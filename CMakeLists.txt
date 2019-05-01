cmake_minimum_required(VERSION 3.12)
project(os_lib)

set(CMAKE_CXX_STANDARD 14)

add_library(prime_slow STATIC slow.cpp)

add_library(prime_fast SHARED fast.cpp)

add_library(prime_fermat SHARED fermat.cpp)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} prime_slow prime_fast -ldl)