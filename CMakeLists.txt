cmake_minimum_required(VERSION 3.28)
project(MDMLD
  VERSION 0.0.1
  DESCRIPTION "An educational Memory Leak Detector"
  LANGUAGES C
)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

# Configuration options
option(MDMLD_BUILD_UNIT_TESTS "Build the MDMLD unit tests" OFF)
option(MDMLD_BUILD_TESTBED "Build the MDMLD testbed" ON)

# Shared library
option(BUILD_SHARED_LIBS "Build MDMLD as a shared library" OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

include(GNUInstallDirs)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(src)

if (MDMLD_BUILD_UNIT_TESTS)
    add_subdirectory(unit-test)
endif ()

if (MDMLD_BUILD_TESTBED)
    add_subdirectory(testbed)
endif ()

install(
  DIRECTORY "${CMAKE_SOURCE_DIR}/include/mdmld"
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

