# file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# list(LENGTH SOURCE_FILES SRC_FILES_SIZE)
# message(STATUS "Found ${SRC_FILES_SIZE} source files")
# foreach(source_file ${SOURCE_FILES})
#     message(STATUS " ${source_file}")
# endforeach()

add_executable(gmp_tests macro_test.cpp)
target_link_libraries(gmp_tests PRIVATE gmp)

if(MSVC)
    # target_compile_options(gmp_tests PRIVATE /Zc:preprocessor)
endif()

add_custom_target(preprocess
    ${CMAKE_CXX_COMPILER} 
        -E -P 
        ${CMAKE_CXX_FLAGS}
        -I${CMAKE_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/macro_test.cpp
        -o ${CMAKE_CURRENT_BINARY_DIR}/macro_test.i
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating preprocessed file: macro_test.i"
)