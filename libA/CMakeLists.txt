cmake_minimum_required(VERSION 2.8)

set(LIB_NAME A)

file(GLOB HS "*.h")
 	
file(GLOB CS "*.c")

add_library(${LIB_NAME} STATIC ${HS} ${CS})