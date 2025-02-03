#include "SpatialAccelerationDifference.h"
#include <quant/units/acceleration/LinearAccelerationDifference.h>
#include <quant/units/acceleration/AngularAccelerationDifference.h>

namespace quant::units::acceleration
{

    SpatialAccelerationDifference::SpatialAccelerationDifference(
        LinearAccelerationDifference const& linear,
        AngularAccelerationDifference const& angular) :
        Difference{SpatialAcceleration{static_cast<LinearAcceleration const>(linear),
                                       static_cast<AngularAcceleration const>(angular)}}
    {
        ;
    }

    std::ostream&
    operator<<(std::ostream& os, SpatialAccelerationDifference const& rhs)
    {
        return os << rhs.to_string();
    }
}  // namespace quant::units::acceleration