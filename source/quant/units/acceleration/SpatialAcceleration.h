#pragma once

#include <quant/geometry/AngularIsometricState.h>
#include <quant/geometry/SpatialState.h>
#include <quant/units/acceleration/forward_declarations.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::acceleration
{

    class SpatialAcceleration : public geometry::SpatialState<SpatialAcceleration>
    {
    public:

        using geometry::SpatialState<SpatialAcceleration>::SpatialState;
    };

    inline std::ostream&
    operator<<(std::ostream& out, SpatialAcceleration const& rhs)
    {
        return out << rhs.to_string();
    }

}  // namespace quant::units::acceleration
