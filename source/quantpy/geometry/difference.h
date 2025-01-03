#pragma once
#include <quant/geometry/ScalarState.h>

#include <pybind11/operators.h>

namespace py = pybind11;

namespace quantpy::geometry
{

    template <typename DerivedT>
    py::class_<DerivedT, quant::geometry::Difference<quant::traits::state_type_of<DerivedT>>>
    registerDifference(py::module& m, std::string const& name)
    {
        using DifferenceT = quant::geometry::Difference<quant::traits::state_type_of<DerivedT>>;
        std::string base_name = "_base_" + name;
        py::class_<DifferenceT>(m, base_name.c_str());

        return py::class_<DerivedT, DifferenceT>(m, name.c_str())
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
