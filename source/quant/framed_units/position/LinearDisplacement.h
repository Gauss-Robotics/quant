#pragma once

#include <quant/framed_geometry/Difference.h>
#include <quant/units/position/LinearDisplacement.h>
#include <quant/units/position/forward_declarations.h>

namespace quant::framed_units::position
{
    class LinearDisplacement : public FramedDifference<units::position::LinearDisplacement>
    {
    public:
        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& os, LinearDisplacement const& rhs);
}  // namespace quant::framed_units::position