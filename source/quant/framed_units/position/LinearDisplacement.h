#pragma once

#include <quant/framed_geometry/Difference.h>
#include <quant/framed_units/position/forward_declarations.h>
#include <quant/units/position/LinearDisplacement.h>

namespace quant::framed_units::position
{
    class LinearDisplacement :
        public framed_geometry::Difference<units::position::LinearDisplacement>
    {
    public:
        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& os, LinearDisplacement const& rhs);
}  // namespace quant::framed_units::position