cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

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

add_library(atomics SHARED
        atomics.h)
set_target_properties(atomics PROPERTIES LINKER_LANGUAGE C)

add_executable(ldupes-run main.c)

target_link_libraries(ldupes atomics)
target_link_libraries(ldupes-run ldupes)
