add_library(geometry SHARED
    ../geometry.h
    ../geometry.cpp
    forward_declarations.h
    forward_declarations.cpp
    constants.h
    constants.cpp

    # Carrier and conversion types.
    Scalar.h
    Scalar.cpp
    Vector.h
    Vector.cpp
    AxisAngle.h
    AxisAngle.cpp

    # Basic state types.
    ScalarState.h
    ScalarState.cpp
    LinearState.h
    LinearState.cpp
        AngularIsometricState.h
        AngularIsometricState.cpp
    SpatialState.h
    SpatialState.cpp
    SpatialIsometricState.h
    SpatialIsometricState.cpp

    Difference.h
    Difference.cpp
    Circa.h
    Circa.cpp

    # Accessors.
    detail/QuantityAccessor.h
    detail/QuantityAccessor.cpp
    detail/DifferenceAccessor.h
    detail/DifferenceAccessor.cpp
)

set_target_properties(geometry
    PROPERTIES
        LINKER_LANGUAGE CXX
)

target_link_libraries(geometry
    PUBLIC
        Eigen3::Eigen
)

add_library(quant::geometry ALIAS geometry)
