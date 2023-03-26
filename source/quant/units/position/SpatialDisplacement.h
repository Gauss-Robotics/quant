#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/position/Pose.h>
#include <quant/units/position_fwd.h>

namespace quant::units::position
{

    class SpatialDisplacement : public Difference<Pose>
    {

    public:
        SpatialDisplacement() : Difference<Pose>()
        {
            ;
        }

        explicit SpatialDisplacement(Pose const& t) : Difference<Pose>(t)
        {
            ;
        }
    };

}  // namespace quant::units::position
