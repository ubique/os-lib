add_library(shared_lib1 SHARED
        hello_world_dynamic1.h
        hello_world_dynamic1.cpp)
set_target_properties(shared_lib1 PROPERTIES LINKER_LANGUAGE CXX)
