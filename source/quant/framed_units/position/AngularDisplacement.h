#pragma once

#include <quant/framed_geometry/Difference.h>
#include <quant/units/position/AngularDisplacement.h>
#include <quant/framed_units/position/forward_declarations.h>

namespace quant::framed_units::position
{

    class AngularDisplacement : public FramedDifference<units::position::AngularDisplacement>
    {
    public:
        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& os, AngularDisplacement const& rhs);
}  // namespace quant::framed_units::position