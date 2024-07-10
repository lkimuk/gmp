# Copyright(c) 2024 Lkimuk Distributed under the MIT License

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

message("\
  ___ __  __ ___ \n\
 / __|  \\/  | _ \\ GMP(Generative Metaprogramming)\n\
| (_ | |\\/| |  _/ version ${PROJECT_VERSION}\n\
 \\___|_|  |_|_|   https://github.com/lkimuk/gmp\n\
")

message("Welcome to the installation wizard for GMP")

# Find all hpp files
file(GLOB_RECURSE HPP_FILES "${PROJECT_SOURCE_DIR}/include/*.hpp")
list(LENGTH HPP_FILES HPP_FILES_SIZE)
message(STATUS "Found ${HPP_FILES_SIZE} hpp files of gmp")
foreach(HPP_FILE ${HPP_FILES})
    message(STATUS "  ${HPP_FILE}")
endforeach()

# Define a shared library target named `gmp`
add_library(gmp SHARED)

target_include_directories(gmp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_options(gmp PRIVATE -Wall -Werror)
target_compile_features(gmp PUBLIC cxx_std_20)

include(GNUInstallDirs)

install(TARGETS gmp
        EXPORT gmp-config
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT gmp-config
        NAMESPACE gmp::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/gmp/cmake
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "gmp-config-version.cmake"
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_DIR}/gmp-config-version.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/gmp/cmake
)