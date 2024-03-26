set(MDMLD_SOURCE_FILES
        ./mld.c
)

set(MDMLD_HEADER_FILES
        ../include/mdmld/md_api.h
        ../include/mdmld/mdmld.h
        ../include/mdmld/mld.h
)

add_library(mdmld ${MDMLD_SOURCE_FILES} ${MDMLD_HEADER_FILES} )
target_include_directories(mdmld
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(mdmld PROPERTIES
        C_STANDARD 17
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS NO
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
)

if (BUILD_SHARED_LIBS)
    message(STATUS "Building shared library")
    target_compile_definitions(mdmld PUBLIC MD_SHARED)
endif ()

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "src" FILES ${MDMLD_SOURCE_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/../include" PREFIX "include" FILES ${MDMLD_HEADER_FILES})

install(
        TARGETS mdmld
        EXPORT mdmldConfig
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION include
)

install(
        EXPORT mdmldConfig
        NAMESPACE mdmld::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mdmld
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/mdmldConfigVersion.cmake"
        COMPATIBILITY AnyNewerVersion
)

install(
        FILES "${CMKAE_CURRENT_BINARY_DIR}/mdmldConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mdmld
)


