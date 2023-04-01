#pragma once

#include <quant/geometry/SpatialDifference.h>
#include <quant/units/position/Pose.h>
#include <quant/units/position_fwd.h>

namespace quant::units::position
{

    class SpatialDisplacement : public geometry::SpatialDifference<Domain>
    {

    public:
        SpatialDisplacement() : geometry::SpatialDifference<Domain>()
        {
            ;
        }

        explicit SpatialDisplacement(Pose const& t) : geometry::SpatialDifference<Domain>(t)
        {
            ;
        }
    };

}  // namespace quant::units::position
