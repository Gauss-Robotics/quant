add_executable(test_units
    main.cpp
    units_tests.h
)

target_link_libraries(test_units
    PUBLIC
        doctest::doctest
        quant::units
)
