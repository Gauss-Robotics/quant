add_library(units SHARED
    ../units.h

    time.h
    time/TimePoint.h
    time/TimePoint.cpp
    time/Duration.h
    time/Duration.cpp
)

set_target_properties(units
    PROPERTIES
        LINKER_LANGUAGE CXX
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/source"
)

target_link_libraries(units
    PRIVATE
        Eigen3::Eigen
        geometry
)
