#pragma once

#include <quant/framed_geometry/Difference.h>
#include <quant/framed_units/position/forward_declarations.h>
#include <quant/units/position/SpatialDisplacement.h>

namespace quant::framed_units::position
{
    class SpatialDisplacement : public FramedDifference<units::position::SpatialDisplacement>
    {
    public:
        using Difference::Difference;
    };
}  // namespace quant::framed_units::position