#pragma once

#include <quant/framed_geometry/Difference.h>
#include <quant/units/acceleration/LinearAccelerationDifference.h>

#include <ostream>

namespace quant::framed_units::acceleration
{

    class LinearAccelerationDifference :
        public framed_geometry::Difference<units::acceleration::LinearAccelerationDifference>
    {
    public:
        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& os, LinearAccelerationDifference const& rhs);

}  // namespace quant::framed_units::acceleration
