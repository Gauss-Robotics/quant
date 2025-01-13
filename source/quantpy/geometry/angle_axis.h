#pragma once

#include <pybind11/pybind11.h>

namespace py = pybind11;
namespace quantpy::geometry {
    void angle_axis(py::module& m);
}