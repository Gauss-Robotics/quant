#pragma once
#include <quant/geometry/LinearState.h>

#include <pybind11/operators.h>

namespace py = pybind11;

namespace quantpy::geometry
{

    template <typename DerivedT>
    py::class_<DerivedT>
    registerLinearState(py::module& m, const std::string& name)
    {
        return py::class_<DerivedT>(m, name.c_str())
            .def(py::init<>())
            .def("zero", &DerivedT::zero)
            .def(py::self == py::self)
            .def(py::self != py::self);
    }
}  // namespace quantpy::geometry
