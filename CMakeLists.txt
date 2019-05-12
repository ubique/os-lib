cmake_minimum_required(VERSION 3.12)

project(Task4)

set(CMAKE_CXX_STANDARD 14)

add_library(hello STATIC hello.cpp)
add_library(answer SHARED answer.cpp)
add_library(compare SHARED comparotor.cpp)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} hello answer compare -ldl)