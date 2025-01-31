set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests")

add_subdirectory(geometry)
add_subdirectory(units)
add_subdirectory(framed_geometry)
add_subdirectory(framed_units)

add_executable(test_all
    main.cpp
    geometry/geometry_tests.h
    units/units_tests.h
    framed_geometry/framed_geometry_tests.h
    framed_units/framed_position_tests.h
    framed_units/framed_velocity_tests.h
)

target_link_libraries(test_all
    PUBLIC
        doctest::doctest
        quant::geometry
        quant::units
        quant::framed_geometry
        quant::framed_units
)
