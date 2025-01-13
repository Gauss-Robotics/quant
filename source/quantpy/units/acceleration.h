#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <Eigen/Dense>

namespace py = pybind11;

namespace quantpy::units::acceleration
{
    void
    angular_acceleration(py::module& m);
    void
    angular_acceleration_difference(py::module& m);

    void
    linear_acceleration(py::module& m);
    void
    linear_acceleration_difference(py::module& m);

    void
    spatial_acceleration(py::module& m);
    void
    spatial_acceleration_difference(py::module& m);
}  // namespace quantpy::units::acceleration