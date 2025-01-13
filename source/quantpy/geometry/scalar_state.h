#pragma once
#include <quant/geometry/ScalarState.h>

#include <pybind11/operators.h>

namespace py = pybind11;

namespace quantpy::geometry
{


    template <typename DerivedT>
    py::class_<DerivedT>
    registerScalarState(py::module& m, const std::string& name)
    {
        auto iadd = [](DerivedT& a, quant::traits::difference_type_of<DerivedT> const& d)
        {
            return a += d;
        };
        auto isub = [](DerivedT& a, quant::traits::difference_type_of<DerivedT> const& d)
        {
            return a -= d;
        };

        return py::class_<DerivedT>(m, name.c_str())
            // .def(py::self + py::self)
            .def("__iadd__", iadd)
            .def("__isub__", isub)
            .def(py::self - py::self)
            .def(py::self / int())
            .def(py::self * int())
            .def(py::self == py::self)
            .def(py::self != py::self)
            .def(-py::self);
    }
}  // namespace quantpy::geometry
