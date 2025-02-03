#pragma once

#include <quant/geometry/SpatialState.h>
#include <quant/units/acceleration/AngularAcceleration.h>
#include <quant/units/acceleration/LinearAcceleration.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::acceleration
{

    class SpatialAcceleration : public geometry::SpatialState<SpatialAcceleration>
    {
    public:

        using geometry::SpatialState<SpatialAcceleration>::SpatialState;
    };

    std::ostream&
    operator<<(std::ostream& out, SpatialAcceleration const& rhs);

}  // namespace quant::units::acceleration
