cmake_minimum_required(VERSION 2.8)

project(lib)

set(CMAKE_CXX_STANDARD 14)

add_library(add STATIC add.cpp)
add_library(subtract SHARED subtract.cpp)
add_library(multiply SHARED multiply.cpp)

add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME} add subtract -ldl)
