file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Assertions are part of these executable tests and must remain active in
# optimized configurations.  Remove the generator-provided definition in this
# directory only; optimization and all other configuration flags are retained.
foreach(config RELEASE RELWITHDEBINFO MINSIZEREL)
    string(REPLACE "/DNDEBUG" "" CMAKE_CXX_FLAGS_${config} "${CMAKE_CXX_FLAGS_${config}}")
    string(REPLACE "-DNDEBUG" "" CMAKE_CXX_FLAGS_${config} "${CMAKE_CXX_FLAGS_${config}}")
endforeach()

list(LENGTH SOURCE_FILES SRC_FILES_SIZE)
message(STATUS "Found ${SRC_FILES_SIZE} source files")
foreach(source_file ${SOURCE_FILES})
    message(STATUS " ${source_file}")

    get_filename_component(file_name ${source_file} NAME)
    string(REPLACE ".cpp" "" name ${file_name})
    message(STATUS " ${name}")
    add_executable(${name} "${name}.cpp")
    target_link_libraries(${name} PRIVATE gmp)
    add_test(NAME ${name} COMMAND ${name})
endforeach()

if(MSVC)
    # set(PREPROCESS_FLAGS "/Zc:preprocessor")
    set(PREPROCESS_FLAGS "")
    # target_compile_options(macro_test PRIVATE /Zc:preprocessor)
    # set(OUTPUT_OPTION "/Fe${CMAKE_CURRENT_BINARY_DIR}/macro_test.i")
else()
    set(PREPROCESS_FLAGS "")
    set(OUTPUT_OPTION > "${CMAKE_CURRENT_BINARY_DIR}/macro_test.i")
endif()

add_custom_target(preprocess
    ${CMAKE_CXX_COMPILER}
        -E -P
        ${CMAKE_CXX_FLAGS}
        ${PREPROCESS_FLAGS}
        -I${CMAKE_SOURCE_DIR}/include
        ${SOURCE_FILES}
        ${OUTPUT_OPTION}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating preprocessed file: macro_test.i"
)
