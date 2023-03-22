add_library(framed_geometry SHARED
    ../framed_geometry.h

    Framed.h
)

set_target_properties(framed_geometry
    PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/source"
)

target_link_libraries(framed_geometry
    PUBLIC
        quant::geometry
)

add_library(quant::framed_geometry ALIAS framed_geometry)
