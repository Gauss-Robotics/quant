#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/position/Pose.h>
#include <quant/units/position_fwd.h>

namespace quant::units::position
{

    class SpatialDisplacement : public geometry::Difference<Pose>
    {

    public:
        using geometry::Difference<Pose>::Difference;
    };

}  // namespace quant::units::position
