#pragma once


#include <quant/geometry/common.h>
#include <quant/units/position/Pose.h>

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

namespace quant
{

    using units::position::SpatialDisplacement;

}
