#pragma once

#include "forward_declarations.h"
#include <quant/units/position/SpatialDisplacement.h>

namespace quant::framed_geometry
{
    class SkewSymmetric
    {
    public:
        SkewSymmetric(units::position::LinearDisplacement const& linear_displacement);
        ;

        Eigen::Matrix3d
        operator*(AngularDisplacement const& angular_displacement) const;

        Eigen::Matrix3d
        matrix() const;

    private:
        Eigen::Matrix3d matrix_;
    };

    class Adjoint
    {
        using Matrix6d = Eigen::Matrix<double, 6, 6>;

    public:
        Adjoint(units::position::SpatialDisplacement const& spatial_displacement);

        Matrix6d
        matrix() const;

    private:
        Matrix6d matrix_;
    };

    inline Adjoint::Matrix6d
    Adjoint::matrix() const
    {
        return matrix_;
    }
}  // namespace quant::framed_geometry