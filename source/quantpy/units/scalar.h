#pragma once

#include <pybind11/pybind11.h>

namespace py = pybind11;
namespace quantpy::units {
    void scalar(py::module& m);
}