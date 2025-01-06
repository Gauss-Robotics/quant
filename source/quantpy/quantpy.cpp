#include <quant/units/acceleration.h>
#include <quant/units/angle.h>
#include <quant/units/angular_acceleration.h>
#include <quant/units/angular_speed.h>
#include <quant/units/electric_current.h>
#include <quant/units/force.h>
#include <quant/units/jerk.h>
#include <quant/units/length.h>
#include <quant/units/mass.h>
#include <quant/units/momentum.h>
#include <quant/units/position.h>
#include <quant/units/speed.h>
#include <quant/units/temperature.h>
#include <quant/units/time.h>
#include <quant/units/velocity.h>

#include <pybind11/pybind11.h>

#include <quantpy/geometry/angle_axis.h>
#include <quantpy/geometry/scalar.h>
#include <quantpy/units/acceleration.h>
#include <quantpy/units/angle.h>
#include <quantpy/units/axis_angle.h>
#include <quantpy/units/scalar.h>
#include <quantpy/units/vector.h>


PYBIND11_MODULE(quantpy, m)
{

    // auto m_geom = m.def_submodule("geometry");
    //
    // quantpy::geometry::scalar(m_geom);
    // quantpy::geometry::vector(m_geom);
    // quantpy::geometry::angle_axis(m_geom);

    auto m_units = m.def_submodule("units");

    quantpy::units::scalar(m_units);
    quantpy::units::vector(m_units);
    quantpy::units::axis_angle(m_units);

    auto m_accel = m_units.def_submodule("acceleration");
    quantpy::units::acceleration::angular_acceleration(m_accel);
    quantpy::units::acceleration::angular_acceleration_difference(m_accel);

    quantpy::units::acceleration::linear_acceleration(m_accel);
    quantpy::units::acceleration::linear_acceleration_difference(m_accel);

    quantpy::units::acceleration::spatial_acceleration(m_accel);
    quantpy::units::acceleration::spatial_acceleration_difference(m_accel);

    auto m_angle = m_units.def_submodule("angle");
    quantpy::units::angle::angle(m_angle);
    quantpy::units::angle::angular_difference(m_angle);
}
