pybind11_add_module(quantpy
        quantpy.cpp

#        geometry/scalar.h
#        geometry/scalar.cpp
#        geometry/angle_axis.h
#        geometry/angle_axis.cpp


        geometry/scalar_state.h
        geometry/linear_state.h
        geometry/difference.h

        units/scalar.h
        units/scalar.cpp
        units/axis_angle.h
        units/axis_angle.cpp
        units/vector.h
        units/vector.cpp

        units/acceleration.h
        units/acceleration.cpp
        units/angle.h
        units/angle.cpp

)
target_link_libraries(quantpy PRIVATE quant::units)
target_link_libraries(quantpy PUBLIC Eigen3::Eigen)