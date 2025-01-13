#include "acceleration.h"

#include <quant/units/acceleration/AngularAcceleration.h>
#include <quant/units/acceleration/LinearAcceleration.h>

#include <quantpy/geometry/angular_state.h>
#include <quantpy/geometry/linear_state.h>

namespace quantpy::units::acceleration
{
    namespace units = quant::units::acceleration;
    namespace geometry = quant::geometry;

    void
    linear_acceleration(py::module& m)
    {
        quantpy::geometry::registerLinearState<units::LinearAcceleration>(m, "LinearAcceleration")
            .def_static("millimeters_per_second_squared",
                        static_cast<units::LinearAcceleration (*)(Eigen::Vector3d const&)>(
                            &units::LinearAcceleration::millimeters_per_second_squared))
            .def_static("meters_per_second_squared",
                        static_cast<units::LinearAcceleration (*)(Eigen::Vector3d const&)>(
                            &units::LinearAcceleration::meters_per_second_squared))
            .def("to_millimeters_per_second_squared",
                 &units::LinearAcceleration::to_millimeters_per_second_squared)
            .def("to_meters_per_second_squared",
                 &units::LinearAcceleration::to_meters_per_second_squared);
    }

    void
    linear_acceleration_difference(py::module& m)
    {
    }

    void
    spatial_acceleration(py::module& m)
    {
    }

    void
    spatial_acceleration_difference(py::module& m) {};

    void
    angular_acceleration(py::module& m)
    {
        quantpy::geometry::registerAngularState<units::AngularAcceleration>(m,
                                                                            "AngularAcceleration")
            .def_static("radians_per_second_squared",
                        [](Eigen::Vector4d const& quaternion)
                        {
                            return units::AngularAcceleration::radians_per_second_squared(
                                Eigen::Quaterniond(quaternion).normalized());
                        })
            .def("to_radians_per_second_squared",
                 &units::AngularAcceleration::to_radians_per_second_squared);
    }

    void
    angular_acceleration_difference(py::module& m) {};

}  // namespace quantpy::units::acceleration