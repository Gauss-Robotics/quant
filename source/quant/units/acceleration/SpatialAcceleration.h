#pragma once

#include <quant/geometry/AngularState.h>
#include <quant/geometry/SpatialIsometricState.h>
#include <quant/units/acceleration/forward_declarations.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::acceleration
{

    class SpatialAcceleration : public geometry::SpatialIsometricState<SpatialAcceleration>
    {
    public:
        SpatialAcceleration(LinearAcceleration const& linear, AngularAcceleration const& angular) :
            SpatialIsometricState(linear, angular)
        {
            ;
        }

        using geometry::SpatialIsometricState<SpatialAcceleration>::SpatialIsometricState;
    };

    inline std::ostream&
    operator<<(std::ostream& out, SpatialAcceleration const& rhs)
    {
        return out << rhs.to_string();
    }

}  // namespace quant::units::acceleration
