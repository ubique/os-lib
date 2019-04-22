cmake_minimum_required(VERSION 2.8)

project(os-lib)

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -Wall -O3 -pedantic -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG ")
endif ()

add_subdirectory(static)
include_directories(static)

add_subdirectory(shared1)
include_directories(shared1)

add_subdirectory(shared2)
include_directories(shared2)

add_executable(os-lib main.cpp)

target_link_libraries(os-lib static_lib)

target_link_libraries(os-lib shared_lib1)

target_link_libraries(os-lib -ldl)