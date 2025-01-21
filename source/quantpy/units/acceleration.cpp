#include "acceleration.h"

#include <quant/units/acceleration.h>

#include <quantpy/geometry/difference.h>
#include <quantpy/geometry/state.h>

namespace quantpy::units::acceleration
{
    namespace units = quant::units::acceleration;
    namespace geometry = quant::geometry;

    void
    linear_acceleration(py::module& m)
    {
        quantpy::geometry::registerState<units::LinearAcceleration>(m, "LinearAcceleration")
            .def_static("millimeters_per_second_squared",
                        static_cast<units::LinearAcceleration (*)(Eigen::Vector3d const&)>(
                            &units::LinearAcceleration::millimeters_per_second_squared))
            .def_static("millimeters_per_second_squared",
                        [](double x, double y, double z)
                        {
                            return units::LinearAcceleration::millimeters_per_second_squared(
                                geometry::Vector{x, y, z});
                        })
            .def_static("meters_per_second_squared",
                        static_cast<units::LinearAcceleration (*)(Eigen::Vector3d const&)>(
                            &units::LinearAcceleration::meters_per_second_squared))
            .def_static("meters_per_second_squared",
                        [](double x, double y, double z)
                        {
                            return units::LinearAcceleration::meters_per_second_squared(
                                geometry::Vector{x, y, z});
                        })
            .def("to_millimeters_per_second_squared",
                 &units::LinearAcceleration::to_millimeters_per_second_squared)
            .def("to_meters_per_second_squared",
                 &units::LinearAcceleration::to_meters_per_second_squared);
    }

    void
    linear_acceleration_difference(py::module& m)
    {
        quantpy::geometry::registerDifference<units::LinearAccelerationDifference>(
            m, "LinearAccelerationDifference")
            .def_static(
                "millimeters_per_second_squared",
                static_cast<units::LinearAccelerationDifference (*)(Eigen::Vector3d const&)>(
                    &units::LinearAccelerationDifference::millimeters_per_second_squared))
            .def_static(
                "millimeters_per_second_squared",
                [](double x, double y, double z)
                {
                    return units::LinearAccelerationDifference::millimeters_per_second_squared(
                        geometry::Vector{x, y, z});
                })
            .def_static(
                "meters_per_second_squared",
                static_cast<units::LinearAccelerationDifference (*)(Eigen::Vector3d const&)>(
                    &units::LinearAccelerationDifference::meters_per_second_squared))
            .def_static("meters_per_second_squared",
                        [](double x, double y, double z)
                        {
                            return units::LinearAccelerationDifference::meters_per_second_squared(
                                geometry::Vector{x, y, z});
                        })
            .def("to_millimeters_per_second_squared",
                 &units::LinearAccelerationDifference::to_millimeters_per_second_squared)
            .def("to_meters_per_second_squared",
                 &units::LinearAccelerationDifference::to_meters_per_second_squared);
    }

    void
    angular_acceleration(py::module& m)
    {
        quantpy::geometry::registerState<units::AngularAcceleration>(m, "AngularAcceleration")
            .def_static("radians_per_second_squared",
                        [](Eigen::Vector4d const& quaternion)
                        {
                            return units::AngularAcceleration::radians_per_second_squared(
                                Eigen::Quaterniond(quaternion));
                        })
            .def_static(
                "radians_per_second_squared",
                [](Eigen::Vector3d const& axis, double angle)
                {
                    return units::AngularAcceleration::radians_per_second_squared(
                        geometry::AxisAngle{.axis = {.x = axis.x(), .y = axis.y(), .z = axis.z()},
                                            .angle = angle});
                })
            .def_static("degrees_per_second_squared",
                        [](Eigen::Vector4d const& quaternion)
                        {
                            return units::AngularAcceleration::radians_per_second_squared(
                                Eigen::Quaterniond(quaternion).normalized());
                        })
            .def_static(
                "degrees_per_second_squared",
                [](Eigen::Vector3d const& axis, double angle)
                {
                    return units::AngularAcceleration::degrees_per_second_squared(
                        geometry::AxisAngle{.axis = {.x = axis.x(), .y = axis.y(), .z = axis.z()},
                                            .angle = angle});
                })
            .def("to_radians_per_second_squared",
                 &units::AngularAcceleration::to_radians_per_second_squared)
            .def("to_degrees_per_second_squared",
                 &units::AngularAcceleration::to_degrees_per_second_squared);
    }

    void
    angular_acceleration_difference(py::module& m)
    {
        quantpy::geometry::registerDifference<units::AngularAccelerationDifference>(m, "AngularAccelerationDifference")
            .def_static("radians_per_second_squared",
                        [](Eigen::Vector4d const& quaternion)
                        {
                            return units::AngularAccelerationDifference::radians_per_second_squared(
                                Eigen::Quaterniond(quaternion));
                        })
            .def_static(
                "radians_per_second_squared",
                [](Eigen::Vector3d const& axis, double angle)
                {
                    return units::AngularAccelerationDifference::radians_per_second_squared(
                        geometry::AxisAngle{.axis = {.x = axis.x(), .y = axis.y(), .z = axis.z()},
                                            .angle = angle});
                })
            .def_static("degrees_per_second_squared",
                        [](Eigen::Vector4d const& quaternion)
                        {
                            return units::AngularAccelerationDifference::radians_per_second_squared(
                                Eigen::Quaterniond(quaternion).normalized());
                        })
            .def_static(
                "degrees_per_second_squared",
                [](Eigen::Vector3d const& axis, double angle)
                {
                    return units::AngularAccelerationDifference::degrees_per_second_squared(
                        geometry::AxisAngle{.axis = {.x = axis.x(), .y = axis.y(), .z = axis.z()},
                                            .angle = angle});
                })
            .def("to_radians_per_second_squared",
                 &units::AngularAccelerationDifference::to_radians_per_second_squared)
            .def("to_degrees_per_second_squared",
                 &units::AngularAccelerationDifference::to_degrees_per_second_squared);
    };

    void
    spatial_acceleration(py::module& m)
    {
        quantpy::geometry::registerState<units::SpatialAcceleration>(m, "SpatialAcceleration");
    }

    void
    spatial_acceleration_difference(py::module& m)
    {
        quantpy::geometry::registerDifference<units::SpatialAccelerationDifference>(m, "SpatialAccelerationDifference");
    };
}  // namespace quantpy::units::acceleration