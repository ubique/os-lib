include_directories(include)
add_library(static STATIC static/static.cpp)
add_library(dyn1 SHARED dyn1/dyn1.cpp)
add_library(dyn2 MODULE dyn2/dyn2.cpp)
