pybind11_add_module(quantpy
        quantpy.cpp

        geometry/scalar.h
        geometry/scalar.cpp
        geometry/scalar_state.h
        geometry/difference.h

        units/acceleration.h
        units/acceleration.cpp
        units/angle.h
        units/angle.cpp
        units/scalar.h
        units/scalar.cpp

)
target_link_libraries(quantpy PRIVATE quant::units)