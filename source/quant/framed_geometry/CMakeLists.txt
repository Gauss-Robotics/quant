add_library(framed_geometry SHARED
    ../framed_geometry.h
    ../framed_geometry_fwd.h

    Framed.h
)

set_target_properties(framed_geometry
    PROPERTIES
        LINKER_LANGUAGE CXX
)

target_link_libraries(framed_geometry
    PUBLIC
        quant::geometry
)

add_library(quant::framed_geometry ALIAS framed_geometry)
