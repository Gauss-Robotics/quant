#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/framed_units/position_fwd.h>
#include <quant/units/position/SpatialDisplacement.h>

namespace quant::framed_geometry
{

    template <>
    struct DefineFramedType<quant::SpatialDisplacement>
    {
        using FramedType = framed_units::position::FramedSpatialDisplacement;
    };

} // namespace quant::framed_geometry

namespace quant::framed_units::position
{
    class FramedSpatialDisplacement : public Framed<SpatialDisplacement>
    {
    public:
        using Framed<SpatialDisplacement>::Framed;
    };

} // namespace quant::framed_units::position

namespace quant
{

    using framed_units::position::FramedSpatialDisplacement;

} // namespace quant
