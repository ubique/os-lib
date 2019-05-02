cmake_minimum_required(VERSION 2.8)

set(LIB_NAME C)

file(GLOB HS "*.h")
 	
file(GLOB CS "*.c")

add_library(${LIB_NAME} SHARED ${HS} ${CS})