#pragma once

#include <quant/geometry/LinearState.h>
#include <quant/units/Vector.h>
#include <quant/units/acceleration/constants.h>
#include <quant/units/acceleration/forward_declarations.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::acceleration
{

    class SpatialAccelerationDifference : public geometry::Difference<SpatialAcceleration>
    {
    public:
        SpatialAccelerationDifference(const LinearAccelerationDifference& linear,
                                      const AngularAccelerationDifference& angular) :
            Difference{SpatialAcceleration{static_cast<LinearAcceleration const>(linear), static_cast<AngularAcceleration const>(angular)}}
        {
            ;
        }

        using geometry::Difference<SpatialAcceleration>::Difference;
    };

    inline std::ostream&
    operator<<(std::ostream& os, SpatialAccelerationDifference const& rhs)
    {
        return os << rhs.to_string();
    }

}  // namespace quant::units::acceleration
