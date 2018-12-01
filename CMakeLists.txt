cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_library(ldupes SHARED
        ldupes.h ldupes.c
        ldupes_error.h
        ldupes_list.h ldupes_list.c
        duplicates_tree.h duplicates_tree.c
        aux.h
        )
add_executable(ldupes_testing main.c)

target_link_libraries(ldupes_testing ldupes)
