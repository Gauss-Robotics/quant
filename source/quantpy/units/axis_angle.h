#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <Eigen/Dense>

#include <quant/units/AxisAngle.h>

namespace py = pybind11;

namespace quantpy::units
{

    void
    axis_angle(py::module& m);

}  // namespace quantpy::units