#pragma once

#include <quant/geometry/SE3TangentState.h>
#include <quant/units/acceleration/AngularAcceleration.h>
#include <quant/units/acceleration/LinearAcceleration.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::acceleration
{

    class SpatialAcceleration : public geometry::SE3TangentState<SpatialAcceleration>
    {
    public:

        using geometry::SE3TangentState<SpatialAcceleration>::SE3TangentState;
    };

    std::ostream&
    operator<<(std::ostream& out, SpatialAcceleration const& rhs);

}  // namespace quant::units::acceleration
