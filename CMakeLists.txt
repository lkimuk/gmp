#   ___ __  __ ___ 
#  / __|  \/  | _ \ GMP(Generative Metaprogramming)
# | (_ | |\/| |  _/ version 0.1.0
#  \___|_|  |_|_|   https://github.com/lkimuk/gmp
#
# SPDX-FileCopyrightText: 2023-2026 Gaoxing Li <https://www.cppmore.com/>
# SPDX-License-Identifier: MIT
#
# This file is part of the GMP (Generative Metaprogramming) library.
# Full project source: https://github.com/lkimuk/gmp

cmake_minimum_required(VERSION 3.12)

# ---------------------------------------------------------------------------------------
# Start gmp project
# ---------------------------------------------------------------------------------------
file(READ "${CMAKE_SOURCE_DIR}/VERSION" PROJECT_VERSION_CONTENT)
string(STRIP "${PROJECT_VERSION_CONTENT}" PROJECT_VERSION)
project(
    gmp
    VERSION ${PROJECT_VERSION}
    DESCRIPTION "A generative metaprogramming library"
    LANGUAGES CXX
)

option(BUILD_TESTS "Build the tests" OFF)
option(BUILD_EXAMPLES "Build the examples" OFF)
option(BUILD_DOCS "Build the API documentation with Doxygen" OFF)

# Display project welcome message and version information
message("\
  ___ __  __ ___ \n\
 / __|  \\/  | _ \\ GMP(Generative Metaprogramming)\n\
| (_ | |\\/| |  _/ version ${PROJECT_VERSION}\n\
 \\___|_|  |_|_|   https://github.com/lkimuk/gmp\n\
")

message(STATUS "Welcome to the installation wizard for GMP")

# ---------------------------------------------------------------------------------------
# Configuration file generation
# ---------------------------------------------------------------------------------------
# Generate version.h from template file version.h.in
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/version.h
    @ONLY
)

# Define an interface library target named 'gmp' (header-only library)
add_library(gmp INTERFACE)

target_include_directories(gmp INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(MSVC)
    target_compile_options(gmp INTERFACE
        /W4
        /wd4514
        /wd4625
        /wd4626
        /wd4820
        /wd5026
        /wd5027
        /wd5045
    )
else()
    target_compile_options(gmp INTERFACE -Wall -Wextra -Wpedantic)
endif()
target_compile_features(gmp INTERFACE cxx_std_20)

# ---------------------------------------------------------------------------------------
# Installation configuration
# ---------------------------------------------------------------------------------------
include(GNUInstallDirs)

# Install the library target
install(TARGETS gmp
        EXPORT gmp-config
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install all header files from include directory
install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install the generated version.h file
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/generated/version.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/gmp
)

# Install the export configuration for CMake package
install(EXPORT gmp-config
        NAMESPACE gmp::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/gmp/cmake
)

# ---------------------------------------------------------------------------------------
# CMake package configuration
# ---------------------------------------------------------------------------------------
include(CMakePackageConfigHelpers)

# Generate version configuration file for CMake package
write_basic_package_version_file(
    "gmp-config-version.cmake"
    COMPATIBILITY SameMajorVersion
)

# Install the generated version configuration file
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/gmp-config-version.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/gmp/cmake
)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# ---------------------------------------------------------------------------------------
# Documentation configuration
# ---------------------------------------------------------------------------------------
if(BUILD_DOCS)
    find_package(Doxygen REQUIRED)

    set(GMP_DOXYGEN_INPUT
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen/mainpage.md"
        "${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen/examples.dox"
    )
    list(TRANSFORM GMP_DOXYGEN_INPUT PREPEND "\"")
    list(TRANSFORM GMP_DOXYGEN_INPUT APPEND "\"")
    string(REPLACE ";" " \\\n    " GMP_DOXYGEN_INPUT "${GMP_DOXYGEN_INPUT}")

    set(GMP_DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/docs/static/api/reference")
    set(GMP_DOXYGEN_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")

    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Doxyfile.in"
        "${GMP_DOXYGEN_CONFIG_FILE}"
        @ONLY
    )

    add_custom_target(docs
        COMMAND ${CMAKE_COMMAND} -E make_directory "${GMP_DOXYGEN_OUTPUT_DIRECTORY}"
        COMMAND ${DOXYGEN_EXECUTABLE} "${GMP_DOXYGEN_CONFIG_FILE}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()
