#include "Adjoint.h"
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/units/position/AngularDisplacement.h>
#include <quant/units/position/LinearDisplacement.h>
#include <quant/units/position/SpatialDisplacement.h>

namespace quant::framed_geometry
{

    SkewSymmetric::SkewSymmetric(units::position::LinearDisplacement const& linear_displacement)
    {
        auto const v = linear_displacement.to_millimeters();
        matrix_ = Eigen::Matrix3d::Zero();
        matrix_(0, 1) = -v.z;
        matrix_(0, 2) = v.y;
        matrix_(1, 0) = v.z;
        matrix_(1, 2) = -v.x;
        matrix_(2, 0) = -v.y;
        matrix_(2, 1) = v.x;
    }

    Eigen::Matrix3d
    SkewSymmetric::operator*(units::position::AngularDisplacement const& angular_displacement) const
    {
        return matrix_ * angular_displacement.to_radians().to_eigen();
    }

    Eigen::Matrix3d
    SkewSymmetric::matrix() const
    {
        return matrix_;
    }

    Adjoint::Adjoint(units::position::SpatialDisplacement const& spatial_displacement)
    {
        using AD = geometry::detail::DifferenceAccessor<units::position::AngularDisplacement>;
        matrix_ = Matrix6d::Zero();
        matrix_.block<3, 3>(0, 0) = AD::representation(spatial_displacement.angular()).matrix();
        matrix_.block<3, 3>(3, 3) = AD::representation(spatial_displacement.angular()).matrix();
        matrix_.block<3, 3>(3, 0) = SkewSymmetric(spatial_displacement.linear()) *
                                    spatial_displacement.angular();
    }
}  // namespace quant::framed_geometry