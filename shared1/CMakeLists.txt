
add_library(shared_lib1 SHARED shared_link1.cpp shared_link1.h)
set_target_properties(shared_lib1 PROPERTIES LINKER_LANGUAGE CXX)
