#include "Adjoint.h"

#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/units/position/AngularDisplacement.h>
#include <quant/units/position/LinearDisplacement.h>
#include <quant/units/position/SpatialDisplacement.h>

namespace quant::framed_geometry
{

    SkewSymmetric3d::SkewSymmetric3d(
        units::position::LinearDisplacement const& linear_displacement) :
        SkewSymmetric3d(linear_displacement.to_meters().to_eigen())
    {
    }

    SkewSymmetric3d::SkewSymmetric3d(Eigen::Vector3d const& vector)
    {
        _matrix = Eigen::Matrix3d::Zero();
        _matrix(0, 1) = -vector.z();
        _matrix(0, 2) = vector.y();
        _matrix(1, 0) = vector.z();
        _matrix(1, 2) = -vector.x();
        _matrix(2, 0) = -vector.y();
        _matrix(2, 1) = vector.x();
    }

    Eigen::Matrix3d
    SkewSymmetric3d::operator*(
        units::position::AngularDisplacement const& angular_displacement) const
    {
        return _matrix * angular_displacement.to_radians().to_eigen();
    }

    Eigen::Matrix3d
    SkewSymmetric3d::operator*(Eigen::Matrix3d const& rhs) const
    {
        return _matrix * rhs;
    }

    Eigen::Matrix3d
    SkewSymmetric3d::matrix() const
    {
        return _matrix;
    }

    SkewSymmetric6d::SkewSymmetric6d(Eigen::Vector<double, 6> const& vector)
    {
        _matrix = Eigen::Matrix4d::Zero();
        _matrix.block<3, 3>(0, 0) = SkewSymmetric3d(vector.head(3)).matrix();
        _matrix.block<3, 1>(0, 3) = vector.tail(3);
    }

    Eigen::Matrix4d
    SkewSymmetric6d::matrix() const
    {
        return _matrix;
    }

    Adjoint::Adjoint(units::position::SpatialDisplacement const& spatial_displacement) :
        Adjoint(geometry::detail::DifferenceAccessor<SpatialDisplacement>::representation(
            spatial_displacement))
    {
    }

    Adjoint::Adjoint(Eigen::Isometry3d const& transformation)
    {
        _matrix = Matrix6d::Zero();
        _matrix.block<3, 3>(0, 0) = transformation.linear();
        _matrix.block<3, 3>(3, 3) = transformation.linear();
        const auto ss = SkewSymmetric3d(transformation.translation());
        const auto pR =  ss * transformation.linear();
        _matrix.block<3, 3>(3, 0) = pR;
    }

    Adjoint::Matrix6d
    Adjoint::matrix() const
    {
        return _matrix;
    }

    Eigen::Vector<double, 6>
    Adjoint::operator*(Eigen::Vector<double, 6> const& rhs) const
    {
        return _matrix * rhs;
    }
}  // namespace quant::framed_geometry