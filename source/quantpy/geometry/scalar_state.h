#pragma once
#include <quant/geometry/ScalarState.h>

#include <pybind11/operators.h>

namespace py = pybind11;

namespace quantpy::geometry
{

    template <typename DerivedT>
    py::class_<DerivedT, quant::geometry::ScalarState<DerivedT>>
    registerScalarState(py::module& m, const std::string& name)
    {
        // using BaseT = quant::geometry::ScalarState<DerivedT>;
        // std::string base_name = "_base_" + name;
        // py::class_<BaseT>(m, base_name.c_str());

        return py::class_<DerivedT>(m, name.c_str())
            .def(py::self + py::self)
            .def(py::self / int())
            .def(py::self * int())
            .def(py::self == py::self)
            .def(py::self != py::self)
            .def(-py::self);
    }
}  // namespace quantpy::geometry
