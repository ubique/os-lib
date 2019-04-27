add_executable(static-linking main.cpp)
target_link_libraries(static-linking PUBLIC framework-static)
target_include_directories(static-linking PRIVATE $<TARGET_PROPERTY:framework-static,INTERFACE_INCLUDE_DIRECTORIES>)

add_executable(shared-linking main.cpp)
target_link_libraries(shared-linking framework-shared)

add_executable(dl-loading dl_loading.cpp)
target_link_libraries(dl-loading -ldl)