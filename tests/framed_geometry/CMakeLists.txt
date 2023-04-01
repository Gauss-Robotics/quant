add_executable(test_framed_geometry
    main.cpp
    framed_geometry_tests.h
)

set_target_properties(test_framed_geometry
    PROPERTIES
        CXX_STANDARD 17
)

target_link_libraries(test_framed_geometry
    PUBLIC
        doctest::doctest
        quant::framed_geometry
)
