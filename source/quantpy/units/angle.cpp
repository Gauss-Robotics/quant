#include "angle.h"

#include <quant/geometry/ScalarState.h>
#include <quant/units/angle/Angle.h>
#include <quant/units/angle/AngularDifference.h>

#include "../geometry/difference.h"
#include "../geometry/scalar_state.h"
#include <pybind11/operators.h>

namespace py = pybind11;

namespace quantpy::units::angle
{
    namespace units = quant::units::angle;
    namespace geometry = quant::geometry;

    void
    angle(py::module& m)
    {
        quantpy::geometry::registerScalarState<units::Angle>(m, "Angle")
            .def_static("radians", [](double d) { return units::Angle::radians(d); })
            .def_static("degrees", [](double d) { return units::Angle::degrees(d); })
            .def("to_radians", &units::Angle::to_radians)
            .def("to_degrees", &units::Angle::to_degrees)
            .def("__float__",
                 [](units::Angle const& a) { return static_cast<double>(a.to_radians()); })
            .def("__repr__", &units::Angle::to_string)
            .def("__str__", &units::Angle::to_string);
    }

    void
    angular_difference(py::module& m)
    {
        quantpy::geometry::registerDifference<units::AngularDifference>(m, "AngularDifference")
            .def_static("radians", [](double d) { return units::AngularDifference::radians(d); })
            .def("to_radians", &units::AngularDifference::to_radians)
            .def("__float__",
                 [](units::AngularDifference const& a) { return static_cast<double>(a.to_radians()); });
    }
}  // namespace quantpy::units::angle
