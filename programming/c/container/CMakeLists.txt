set(MODULE_NAME container)
message(STATUS "module: ${MODULE_NAME}")
set(
    SOURCE
    array_list.c
)

add_library(${MODULE_NAME} SHARED ${SOURCE})
add_library(${MODULE_NAME}_static STATIC ${SOURCE})
set_target_properties(${MODULE_NAME}_static PROPERTIES OUTPUT_NAME ${MODULE_NAME})
set_target_properties(${MODULE_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(${MODULE_NAME}_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

if (CMAKE_BUILD_TYPE STREQUAL debug)
    add_executable(${MODULE_NAME}_test ${SOURCE} test/main.c)
    set_target_properties(${MODULE_NAME}_test PROPERTIES OUTPUT_NAME ${MODULE_NAME})
    set_target_properties(${MODULE_NAME}_test PROPERTIES CLEAN_DIRECT_OUTPUT 1)
endif()
