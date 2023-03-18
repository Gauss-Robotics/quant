add_library(geometry SHARED
    ../geometry.h

    common.h
    common.cpp

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
    PRIVATE
        Eigen3::Eigen
)
