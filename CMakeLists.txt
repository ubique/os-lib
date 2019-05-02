cmake_minimum_required(VERSION 2.8)

project(lib)

add_subdirectory(libA)
add_subdirectory(libB)
add_subdirectory(libC)

add_executable(main main.c)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libA ${CMAKE_CURRENT_SOURCE_DIR}/libB)

target_link_libraries(main A)
target_link_libraries(main B)
target_link_libraries(main dl)