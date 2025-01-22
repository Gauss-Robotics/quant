add_executable(test_framed_units
        main.cpp
        framed_units_tests.h
)

target_link_libraries(test_framed_units
        PUBLIC
        doctest::doctest
        quant::framed_units
)
