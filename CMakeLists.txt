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
project(
    gmp
    VERSION 0.1.0
    DESCRIPTION "A generative metaprogramming library"
    LANGUAGES CXX
)

option(BUILD_TESTS "Build the tests" OFF)

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

target_compile_options(gmp INTERFACE -Wall)
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