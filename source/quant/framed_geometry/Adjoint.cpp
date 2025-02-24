#include "Adjoint.h"

#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/units/position/SpatialDisplacement.h>

#include "Hat.h"

namespace quant::framed_geometry
{

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
        auto const ss = HatSO3(transformation.translation());
        auto const pR = ss * transformation.linear();
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