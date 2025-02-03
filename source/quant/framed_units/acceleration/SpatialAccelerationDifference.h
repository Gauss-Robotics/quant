#pragma once

#include <quant/framed_geometry/Difference.h>
#include <quant/units/acceleration/SpatialAccelerationDifference.h>
#include <quant/framed_units/acceleration/forward_declarations.h>

#include <ostream>

namespace quant::framed_units::acceleration
{

    class SpatialAccelerationDifference :
        public framed_geometry::Difference<units::acceleration::SpatialAccelerationDifference>
    {
    public:
        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& os, SpatialAccelerationDifference const& rhs);

}  // namespace quant::framed_units::acceleration
