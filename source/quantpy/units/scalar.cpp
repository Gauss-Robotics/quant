#include "scalar.h"

#include <quant/geometry/Scalar.h>
#include <quant/units/Scalar.h>

namespace quantpy::units
{
    void
    scalar(py::module& m)
    {
        py::class_<quant::units::Scalar>(m, "Scalar")
            .def(py::init<double, std::string, std::string>(), py::arg("value"), py::arg("quantity_name"), py::arg("unit_symbol"))
            .def("__mul__", &quant::units::Scalar::operator*)
            .def("__truediv__", &quant::units::Scalar::operator/)
            .def("__float__", &quant::units::Scalar::operator double)
            .def("__repr__", &quant::units::Scalar::to_string)
            .def("__str__", &quant::units::Scalar::to_string)
            .def_readwrite("value", &quant::units::Scalar::value)
            .def_readonly("quantity_name", &quant::units::Scalar::quantity_name)
            .def_readonly("unit_symbol", &quant::units::Scalar::unit_symbol);
    }
}  // namespace quantpy::units
