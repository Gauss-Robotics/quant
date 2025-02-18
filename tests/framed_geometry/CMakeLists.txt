add_executable(test_framed_geometry
    main.cpp
    DummyLinearState.h
    framed_geometry_tests.h
)

target_link_libraries(test_framed_geometry
    PUBLIC
        doctest::doctest
        quant::framed_geometry
)
