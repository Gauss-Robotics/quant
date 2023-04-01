set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/test")

add_executable(geometry_test
    geometry/main.cpp
)
set_target_properties(geometry_test
    PROPERTIES
        CXX_STANDARD 17
)
target_link_libraries(geometry_test
    PUBLIC
        doctest::doctest
        quant::geometry
)

add_executable(units_test
    units/main.cpp
)
set_target_properties(units_test
    PROPERTIES
        CXX_STANDARD 17
)
target_link_libraries(units_test
    PUBLIC
        doctest::doctest
        quant::units
)

add_executable(framed_geometry_test
    framed_geometry/main.cpp
)
set_target_properties(framed_geometry_test
    PROPERTIES
        CXX_STANDARD 17
)
target_link_libraries(framed_geometry_test
    PUBLIC
        doctest::doctest
        quant::framed_geometry
)
