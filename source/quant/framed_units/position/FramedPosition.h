#pragma once

#include <Eigen/Geometry>

#include <quant/framed_geometry/Framed.h>
#include <quant/units/position/Position.h>

namespace quant::framed_units::position
{

    class FramedPosition : public Framed<Position>
    {

    public:
        FramedPosition(Position const& p, FrameData const& frame) : Framed<Position>(p, frame)
        {
            ;
        }
    };

} // namespace quant::framed_units::position

namespace quant
{

    using framed_units::position::FramedPosition;

} // namespace quant