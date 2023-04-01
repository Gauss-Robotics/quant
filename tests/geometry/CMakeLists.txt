add_executable(test_geometry
    main.cpp
    geometry_tests.h
)

set_target_properties(test_geometry
    PROPERTIES
        CXX_STANDARD 17
)

target_link_libraries(test_geometry
    PUBLIC
        doctest::doctest
        quant::geometry
)
