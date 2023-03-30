#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/framed_units/position_fwd.h>
#include <quant/units/position/SpatialDisplacement.h>

namespace quant::framed_geometry
{

    template <>
    struct DefineFramedType<quant::SpatialDisplacement>
    {
        using FramedType = framed_units::position::SpatialDisplacement;
    };

}  // namespace quant::framed_geometry

namespace quant::framed_units::position
{
    class SpatialDisplacement : public Framed<position::SpatialDisplacement>
    {
    public:
        using Framed<position::SpatialDisplacement>::Framed;
    };

}  // namespace quant::framed_units::position
