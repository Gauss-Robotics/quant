#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/framed_units/position_fwd.h>
#include <quant/units/position/SpatialDisplacement.h>

namespace quant::framed_units::position
{

    class SpatialDisplacement : public Framed<units::position::SpatialDisplacement>
    {
    public:
        using Framed<units::position::SpatialDisplacement>::Framed;
    };

}  // namespace quant::framed_units::position
