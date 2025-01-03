#pragma once
#include <pybind11/pybind11.h>

namespace py = pybind11;
namespace quantpy::units::angle {
    void angle(py::module& m);
    void angular_difference(py::module& m);
}