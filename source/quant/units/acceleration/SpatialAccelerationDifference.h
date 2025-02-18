#pragma once

#include <quant/framed_geometry/Difference.h>
#include <quant/units/acceleration/SpatialAcceleration.h>

#include <ostream>

namespace quant::units::acceleration
{

    class SpatialAccelerationDifference : public geometry::Difference<SpatialAcceleration>
    {
    public:
        SpatialAccelerationDifference(LinearAccelerationDifference const& linear,
                                      AngularAccelerationDifference const& angular);

        using geometry::Difference<SpatialAcceleration>::Difference;
    };

    std::ostream&
    operator<<(std::ostream& os, SpatialAccelerationDifference const& rhs);

}  // namespace quant::units::acceleration
