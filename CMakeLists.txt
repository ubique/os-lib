cmake_minimum_required(VERSION 3.10)
project(os_lib)

set(CMAKE_CXX_STANDARD 14)

add_executable(os_lib main.cpp static/multiplication.cpp static/multiplication.h secondDynamic/exponentiation.cpp secondDynamic/exponentiation.h firstDynamic/logarithm.cpp firstDynamic/logarithm.h)