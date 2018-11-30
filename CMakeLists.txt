cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 11)

add_library(rbtree SHARED rbtree.h rbtree.c)

add_library(ldupes SHARED
  ldupes.h ldupes.c
  cluster_node.h cluster_node.c
  file_list.h file_list.c)
add_executable(ldupes_testing main.c)

target_link_libraries(ldupes rbtree)
target_link_libraries(ldupes_testing ldupes)
