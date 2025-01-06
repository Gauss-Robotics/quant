#include "axis_angle.h"

#include <format>
#include <iomanip>

quant::units::AxisAngle
construct(double angle,
          Eigen::Vector3d const& axis,
          std::string_view const& quantity_name,
          std::string_view const& unit_symbol)
{
    Eigen::AngleAxisd const aa(angle, axis.normalized());
    return {aa, quantity_name, unit_symbol};
}

namespace quantpy::units
{
    std::string
    make_repr(quant::units::AxisAngle const& aa)
    {
        return std::format(
            "AxisAngle({:.2f}, {}, '{}', '{}')", aa.angle, aa.axis.to_string(), aa.quantity_name, aa.unit_symbol);;
    }

    void
    axis_angle(py::module& m)
    {
        py::class_<quant::units::AxisAngle>(m, "AxisAngle")
            .def(py::init(&construct),
                 py::arg("angle"),
                 py::arg("axis"),
                 py::arg("quantity_name"),
                 py::arg("unit_symbol"))
            .def("__str__", &quant::units::AxisAngle::to_string)
            .def("__repr__", &make_repr)
            .def_readonly("unit_symbol", &quant::units::AxisAngle::unit_symbol)
            .def_readonly("quantity_name", &quant::units::AxisAngle::quantity_name)
            .def_property(
                "axis",
                [](quant::units::AxisAngle const& aa) { return aa.axis.to_eigen(); },
                [](quant::units::AxisAngle& aa, Eigen::Vector3d const& axis)
                { aa.axis = quant::geometry::Vector::from_eigen(axis); })
            .def_readwrite("angle", &quant::units::AxisAngle::angle);
    }

}  // namespace quantpy::units
