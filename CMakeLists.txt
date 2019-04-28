cmake_minimum_required(VERSION 3.10)
project(prog)
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++17 -O3 -Wl,-rpath,.")
set(CMAKE_LINK_DEF_FILE_FLAG "-Wl,-rpath,.")
set(CMAKE_CXX_STANDARD 17)
file(GLOB SOURCES "./*.cpp" "./*.h")
add_executable(prog ${SOURCES})

target_link_libraries (prog ${CMAKE_DL_LIBS})
