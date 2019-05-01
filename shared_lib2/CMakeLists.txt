add_library(shared_lib2 SHARED
        hello_world_dynamic2.h
        hello_world_dynamic2.cpp)
set_target_properties(shared_lib2 PROPERTIES LINKER_LANGUAGE CXX)
