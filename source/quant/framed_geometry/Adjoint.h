#pragma once

#include <Eigen/Geometry>

#include "forward_declarations.h"

namespace quant::framed_geometry
{

    class Adjoint
    {
        using Matrix6d = Eigen::Matrix<double, 6, 6>;

    public:
        Adjoint(units::position::SpatialDisplacement const& spatial_displacement);
        Adjoint(Eigen::Isometry3d const& transformation);

        Matrix6d
        matrix() const;

        Eigen::Vector<double, 6>
        operator*(Eigen::Vector<double, 6> const& rhs) const;

    private:
        Matrix6d _matrix;
    };
}  // namespace quant::framed_geometry