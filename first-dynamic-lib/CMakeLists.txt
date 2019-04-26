add_library(first-dynamic-lib SHARED tweetybird.cpp)
set_target_properties(first-dynamic-lib PROPERTIES LINKER_LANGUAGE CXX)