cmake_minimum_required(VERSION 2.8)

project(os-lib)
add_executable(${PROJECT_NAME} "main.cpp")

add_library(xxhash STATIC "xxhash.hpp")
set_target_properties(xxhash PROPERTIES LINKER_LANGUAGE CXX)

add_library(roots SHARED "roots.h")
set_target_properties(roots PROPERTIES LINKER_LANGUAGE CXX)

add_library(useless SHARED "useless.cpp")
set_target_properties(useless PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${PROJECT_NAME} xxhash)
target_link_libraries(${PROJECT_NAME} roots)
target_link_libraries(${PROJECT_NAME} -ldl)
