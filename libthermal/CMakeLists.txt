project(thermal)

add_library(thermal STATIC libthermal.c)

target_include_directories(thermal PUBLIC .)
