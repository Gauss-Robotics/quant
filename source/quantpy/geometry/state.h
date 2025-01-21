#pragma once
#include <quant/geometry/AngularState.h>

#include <pybind11/operators.h>

namespace py = pybind11;

namespace quantpy::geometry
{

    template <typename DerivedT>
        requires quant::traits::state<DerivedT>
    py::class_<DerivedT>
    registerState(py::module& m, std::string const& name)
    {
        using DifferenceT = quant::traits::difference_type_of<DerivedT>;

        auto iadd = [](DerivedT& a, DifferenceT const& d) { return a += d; };
        auto isub = [](DerivedT& a, DifferenceT const& d) { return a -= d; };

        return py::class_<DerivedT>(m, name.c_str())
            .def(py::init<>())
            .def("zero", &DerivedT::zero)
            .def("__str__", &DerivedT::to_string)
            .def("__repr__", &DerivedT::to_string)
            .def(py::self == py::self)
            .def(py::self != py::self)
            .def(py::self - py::self)
            .def(py::self + DifferenceT())
            .def(py::self - DifferenceT())
            .def("__iadd__", iadd)
            .def("__isub__", isub)
            .def("is_approx", &DerivedT::is_approx)
            .def(-py::self);
    }
}  // namespace quantpy::geometry
