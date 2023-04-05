add_library(geometry SHARED
    ../geometry.h
    ../geometry_fwd.h

    # Carrier and conversion types.
    Scalar.h
    Vector.h
    AxisAngle.h

    # Basic state types.
    ScalarState.h
    LinearState.h
    AngularState.h
    SpatialState.h
    SpatialIsometricState.h

    # Basic difference types.
    Difference.h
    ScalarDifference.h
    LinearDifference.h
    AngularDifference.h
    SpatialDifference.h

    Circa.h

    # Accessors.
    detail/QuantityAccessor.h
    detail/DifferenceAccessor.h
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
