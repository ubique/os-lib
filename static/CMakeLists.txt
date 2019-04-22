
add_library(static_lib STATIC static_link.h static_link.cpp)
set_target_properties(static_lib PROPERTIES LINKER_LANGUAGE CXX)