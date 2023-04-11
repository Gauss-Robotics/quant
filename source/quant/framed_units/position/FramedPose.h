#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/framed_units/position_fwd.h>
#include <quant/units/position/Pose.h>

namespace quant::framed_units::position
{

    class Pose : public Framed<units::position::Pose>
    {
    public:
        using Framed<units::position::Pose>::Framed;
    };

}  // namespace quant::framed_units::position
