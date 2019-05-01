project(libfnv)

add_library(fnv32 SHARED libfnv32.c)

target_include_directories(fnv32 PUBLIC .)
