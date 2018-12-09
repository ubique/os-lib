cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} --sanitize=address,undefined")
set(CMAKE_C_FLAGS_RELEASE  "${CMAKE_C_FLAGS_RELEASE} -O3")

add_library(ldupes SHARED
        ldupes.h ldupes.c
        ld_context.h ld_context.c
        ld_error.h
        ld_ranked_list.h
        ld_file.h
        ld_duplicates_tree.h ld_duplicates_tree.c

        aux.h aux.c

        rbtree.h rbtree.c
        xxhash.h xxhash.c
        )

add_executable(ldupes_testing main.c)

target_link_libraries(ldupes_testing ldupes)
