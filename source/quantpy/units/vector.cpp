#include "vector.h"

#include <quant/units/Vector.h>

#include <format>

namespace quantpy::units
{
    std::string
    make_repr(quant::units::Vector const& v)
    {
        return std::format(
            "Vector([{}, {}, {}], '{}', '{}')", v.x, v.y, v.z, v.quantity_name, v.unit_symbol);
    }

    void
    vector(py::module& m)
    {
        py::class_<quant::units::Vector>(m, "Vector")
            .def(py::init<Eigen::Vector3d, std::string_view const&, std::string_view const&>(),
                 py::arg("vector"),
                 py::arg("quantity_name"),
                 py::arg("unit_symbol"))
            .def("__mul__", &quant::units::Vector::operator*)
            .def("__truediv__", &quant::units::Vector::operator/)
            .def("__repr__", &make_repr)
            .def("__str__", &quant::units::Vector::to_string)
            .def("norm", &quant::units::Vector::norm)
            .def_static("unit_x", &quant::units::Vector::unit_x)
            .def_static("unit_y", &quant::units::Vector::unit_y)
            .def_static("unit_z", &quant::units::Vector::unit_z)
            .def_readwrite("x", &quant::units::Vector::x)
            .def_readwrite("y", &quant::units::Vector::y)
            .def_readwrite("z", &quant::units::Vector::z)
            .def_readonly("unit_symbol", &quant::units::Vector::unit_symbol)
            .def_readonly("quantity_name", &quant::units::Vector::quantity_name);
    }
}  // namespace quantpy::units