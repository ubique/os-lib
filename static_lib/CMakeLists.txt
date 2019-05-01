add_library(static_lib STATIC
        hello_world_static.h
        hello_world_static.cpp)
set_target_properties(static_lib PROPERTIES LINKER_LANGUAGE CXX)
