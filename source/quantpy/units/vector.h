#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <Eigen/Dense>

namespace py = pybind11;
namespace quantpy::units {
    void vector(py::module& m);
}