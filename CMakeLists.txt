cmake_minimum_required(VERSION 3.0)

project(lib C)

add_subdirectory(libfoo)
add_subdirectory(libbar)
add_subdirectory(libbaz)

add_executable(foobarbaz foobarbaz.c)

target_include_directories(foobarbaz PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/libfoo
    ${CMAKE_CURRENT_SOURCE_DIR}/libbar
)

target_link_libraries(foobarbaz foo)
target_link_libraries(foobarbaz bar)
target_link_libraries(foobarbaz dl)

install(TARGETS foobarbaz
        RUNTIME DESTINATION bin)
