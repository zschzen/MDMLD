set(TESTBED_SOURCE_FILES
        main.c
)

set(TESTBED_HEADER_FILES
)

add_executable(testbed ${TESTBED_SOURCE_FILES} ${TESTBED_HEADER_FILES})
target_include_directories(testbed PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(testbed PUBLIC mdmld)

set_target_properties(testbed PROPERTIES
        C_STANDARD 17
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS NO
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TESTBED_SOURCE_FILES} ${TESTBED_HEADER_FILES})

