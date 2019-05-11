add_library(static_lb STATIC static/static.cpp)
add_library(dyn1_lb SHARED dyn1/dyn1.cpp)
add_library(dyn2_lb MODULE dyn2/dyn2.cpp)
include_directories(include)
