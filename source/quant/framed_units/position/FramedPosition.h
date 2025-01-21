#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/framed_units/position/forward_declarations.h>
#include <quant/units/position/Position.h>
#include <quant/units/position/SpatialDisplacement.h>

namespace quant::framed_geometry
{
    template <>
    struct FrameConversion<units::position::Position>
    {
        static units::position::Position&
        convert(units::position::Position& pose,
                units::position::SpatialDisplacement const& /*transform*/)
        {
            // TODO: implement
            return pose;
        }
    };
}  // namespace quant::framed_geometry

namespace quant::framed_units::position
{

    class Position : public Framed<units::position::Position>
    {

    public:
        Position(units::position::Position const& p, FrameIdentifier const& frame) :
            Framed<units::position::Position>(p, frame)
        {
            ;
        }
    };

}  // namespace quant::framed_units::position
