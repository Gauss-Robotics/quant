#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/units/position/Position.h>

#include <Eigen/Geometry>

namespace quant::framed_units::position
{

    class Position : public Framed<position::Position>
    {

    public:
        Position(position::Position const& p, FrameData const& frame) :
            Framed<position::Position>(p, frame)
        {
            ;
        }
    };

}  // namespace quant::framed_units::position
