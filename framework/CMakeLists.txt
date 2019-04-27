project(framework)

set(sources
        src/lib.cpp
        )

add_library(${PROJECT_NAME}-object OBJECT ${sources})

target_include_directories(${PROJECT_NAME}-object
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
        )
set_target_properties(${PROJECT_NAME}-object PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(${PROJECT_NAME}-static STATIC)
target_link_libraries(${PROJECT_NAME}-static PUBLIC ${PROJECT_NAME}-object)
add_library(${PROJECT_NAME}-shared SHARED)
target_link_libraries(${PROJECT_NAME}-shared PUBLIC ${PROJECT_NAME}-object)
