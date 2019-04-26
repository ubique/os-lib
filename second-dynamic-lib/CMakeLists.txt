add_library(second-dynamic-lib SHARED killme.cpp)
set_target_properties(second-dynamic-lib PROPERTIES LINKER_LANGUAGE CXX)