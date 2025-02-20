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
    T3State.h
    T3State.cpp
    T3TangentState.h
    T3TangentState.cpp
    SO3TangentState.h
    SO3TangentState.cpp
    SO3State.h
    SO3State.cpp
    SE3TangentState.h
    SE3TangentState.cpp
    SE3State.h
    SE3State.cpp

    Difference.h
    Difference.cpp
    Circa.h
    Circa.cpp

    # Accessors.
    detail/QuantityAccessor.h
    detail/QuantityAccessor.cpp
    detail/DifferenceAccessor.h
    detail/DifferenceAccessor.cpp

    # Operators.
    detail/ArithmeticOperators.h
    detail/ManifoldOperators.h
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
