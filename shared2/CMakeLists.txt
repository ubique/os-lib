
add_library(shared_lib2 SHARED shared_link2.cpp shared_link2.h)
set_target_properties(shared_lib2 PROPERTIES LINKER_LANGUAGE CXX)