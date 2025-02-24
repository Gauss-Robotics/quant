#include "Hat.h"

#include <quant/units/position/AngularDisplacement.h>
#include <quant/units/position/LinearDisplacement.h>

namespace quant::framed_geometry
{
    HatSO3::HatSO3(units::position::LinearDisplacement const& linear_displacement) :
        HatSO3(linear_displacement.to_meters().to_eigen())
    {
    }

    HatSO3::HatSO3(Eigen::Vector3d const& vector)
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
    HatSO3::operator*(units::position::AngularDisplacement const& angular_displacement) const
    {
        return _matrix * angular_displacement.to_radians().to_eigen();
    }

    Eigen::Matrix3d
    HatSO3::operator*(Eigen::Matrix3d const& rhs) const
    {
        return _matrix * rhs;
    }

    Eigen::Matrix3d
    HatSO3::matrix() const
    {
        return _matrix;
    }

    HatSE3::HatSE3(Eigen::Vector<double, 6> const& vector)
    {
        _matrix = Eigen::Matrix4d::Zero();
        _matrix.block<3, 3>(0, 0) = HatSO3(vector.head(3)).matrix();
        _matrix.block<3, 1>(0, 3) = vector.tail(3);
    }

    Eigen::Matrix4d
    HatSE3::matrix() const
    {
        return _matrix;
    }
}  // namespace quant::framed_geometry