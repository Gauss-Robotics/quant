add_executable(test_geometry
    main.cpp
    geometry_tests.h
)

target_link_libraries(test_geometry
    PUBLIC
        doctest::doctest
        quant::geometry
        quant::units
)
