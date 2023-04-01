add_executable(test_units
    main.cpp
    units_tests.h
)

set_target_properties(test_units
    PROPERTIES
        CXX_STANDARD 17
)

target_link_libraries(test_units
    PUBLIC
        doctest::doctest
        quant::units
)
