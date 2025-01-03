#include "scalar.h"

#include <quant/geometry/Scalar.h>

namespace quantpy::geometry
{
    void
    scalar(py::module& m)
    {
        py::class_<quant::geometry::Scalar>(m, "Scalar")
            .def(py::init<double>(), py::arg("value") = 0.0)
            .def("__mul__", &quant::geometry::Scalar::operator*)
            .def("__truediv__", &quant::geometry::Scalar::operator/)
            .def("__float__", &quant::geometry::Scalar::operator double)
            .def("__repr__", &quant::geometry::Scalar::to_string)
            .def("__str__", &quant::geometry::Scalar::to_string);
    }
}  // namespace quantpy::geometry
