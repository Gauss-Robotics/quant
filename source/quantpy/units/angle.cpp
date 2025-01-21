#include "angle.h"

#include <quant/geometry/ScalarState.h>
#include <quant/units/angle/Angle.h>
#include <quant/units/angle/AngularDifference.h>

#include <format>

#include <quantpy/geometry/difference.h>
#include <quantpy/geometry/state.h>
#include <pybind11/operators.h>

namespace py = pybind11;

namespace quantpy::units::angle
{
    namespace units = quant::units::angle;
    namespace geometry = quant::geometry;

    std::string make_angle_repr(const units::Angle& a)
    {
        return std::format("Angle({})", a.to_degrees().to_string());
    }

    void angle_inplace_add(units::Angle& a, units::AngularDifference const& d)
    {
        a += d;
    }
    void
    angle(py::module& m)
    {
        quantpy::geometry::registerState<units::Angle>(m, "Angle")
            .def_static("radians", [](double d) { return units::Angle::radians(d); })
            .def_static("degrees", [](double d) { return units::Angle::degrees(d); })
            .def("to_radians", &units::Angle::to_radians)
            .def("to_degrees", &units::Angle::to_degrees)
            // .def("__iadd__", &units::Angle::operator+=)
            .def("__repr__", &make_angle_repr)
            .def("__str__", &units::Angle::to_string);
    }

    void
    angular_difference(py::module& m)
    {
        quantpy::geometry::registerDifference<units::AngularDifference>(m, "AngularDifference")
            .def_static("radians", [](double d) { return units::AngularDifference::radians(d); })
            .def_static("degrees", [](double d) { return units::AngularDifference::degrees(d); })
            .def("to_radians", &units::AngularDifference::to_radians)
            .def("to_degrees", &units::AngularDifference::to_degrees)
            .def("__float__",
                 [](units::AngularDifference const& a) { return static_cast<double>(a.to_radians()); });
    }
}  // namespace quantpy::units::angle
