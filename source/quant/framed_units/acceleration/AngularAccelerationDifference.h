#pragma once

#include <quant/framed_geometry/Difference.h>
#include <quant/units/acceleration/AngularAccelerationDifference.h>
#include <quant/framed_units/acceleration/forward_declarations.h>

namespace quant::framed_units::acceleration
{
    class AngularAccelerationDifference :
        public framed_geometry::Difference<units::acceleration::AngularAccelerationDifference>
    {
    public:
        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& out, AngularAccelerationDifference const& rhs);
}  // namespace quant::framed_units::acceleration