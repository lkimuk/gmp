add_executable(gmp_example_reflection_enum
    reflection_enum.cpp
)
target_link_libraries(gmp_example_reflection_enum PRIVATE gmp)

add_executable(gmp_example_aggregate_reflection
    aggregate_reflection.cpp
)
target_link_libraries(gmp_example_aggregate_reflection PRIVATE gmp)

add_executable(gmp_example_named_operator
    named_operator.cpp
)
target_link_libraries(gmp_example_named_operator PRIVATE gmp)

add_executable(gmp_example_type_name_and_size
    type_name_and_size.cpp
)
target_link_libraries(gmp_example_type_name_and_size PRIVATE gmp)

add_executable(gmp_example_serialization
    serialization.cpp
)
target_link_libraries(gmp_example_serialization PRIVATE gmp)
