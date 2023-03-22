add_library(geometry SHARED
    ../geometry.h
    ../geometry_fwd.h

    Vector.h
    AxisAngle.h
    Spatial.h
    Difference.h

    ScalarQuantity.h
    VectorQuantity.h
    QuaternionQuantity.h
    IsometryQuantity.h
)

set_target_properties(geometry
    PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/source"
)

target_link_libraries(geometry
    PUBLIC
        Eigen3::Eigen
)

add_library(quant::geometry ALIAS geometry)
