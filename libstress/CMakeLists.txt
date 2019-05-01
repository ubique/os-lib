project(libstress)

add_library(stress SHARED libstress.c)

target_include_directories(stress PUBLIC .)
