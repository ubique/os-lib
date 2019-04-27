cmake_minimum_required(VERSION 3.0)

add_library(bar SHARED bar.c bar.h)

install(TARGETS bar
        LIBRARY DESTINATION bin)
