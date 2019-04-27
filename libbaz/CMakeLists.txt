cmake_minimum_required(VERSION 3.0)

add_library(baz SHARED baz.c baz.h)

install(TARGETS baz
        LIBRARY DESTINATION bin)
