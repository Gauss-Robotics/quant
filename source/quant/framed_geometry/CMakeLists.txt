add_library(framed_geometry SHARED
        ../framed_geometry.h
        forward_declarations.h

        Framed.h
        Difference.h
)

set_target_properties(framed_geometry
        PROPERTIES
        LINKER_LANGUAGE CXX
)

target_link_libraries(framed_geometry
        PUBLIC
        quant::geometry
        quant::units
)

add_library(quant::framed_geometry ALIAS framed_geometry)
