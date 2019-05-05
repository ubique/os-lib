cmake_minimum_required(VERSION 2.8)

project(os_lib)

add_subdirectory(libfnv)
add_subdirectory(libthermal)
add_subdirectory(libstress)

add_executable(main main.c)

target_link_libraries(main fnv32 thermal dl)

