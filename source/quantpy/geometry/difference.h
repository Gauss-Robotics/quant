#pragma once
#include <quant/geometry/ScalarState.h>

#include <pybind11/operators.h>

namespace py = pybind11;

namespace quantpy::geometry
{

    template <typename DerivedT>
    py::class_<DerivedT>
    registerDifference(py::module& m, std::string const& name)
    {
        using DifferenceT = quant::geometry::Difference<quant::traits::state_type_of<DerivedT>>;

        return py::class_<DerivedT>(m, name.c_str())
            .def("__repr__", &DifferenceT::to_string)
            .def("__str__", &DifferenceT::to_string)
            .def_static("zero", &DifferenceT::zero)
            .def(py::self == py::self)
            .def(py::self != py::self)
            .def(py::self + py::self)
            .def(py::self / int())
            .def(py::self * int())

            .def(-py::self);
    }
}  // namespace quantpy::geometry
