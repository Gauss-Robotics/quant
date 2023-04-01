#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/framed_units/position_fwd.h>
#include <quant/units/position/Position.h>

#include <Eigen/Geometry>

namespace quant::framed_units::position
{

    class Position : public Framed<units::position::Position>
    {

    public:
        Position(units::position::Position const& p, FrameData const& frame) :
            Framed<units::position::Position>(p, frame)
        {
            ;
        }
    };

}  // namespace quant::framed_units::position
