#pragma once


#include <Eigen/Geometry>

#include <quant/core/length/Position.h>
#include <quant/core/length/frame/FramedMixin.h>


namespace quant::position
{

    class FramedPosition : public Position, public FramedMixin
    {
    public:
        FramedPosition(const Position& p, const FramedMixin& m) : Position(p), FramedMixin(m)
        {
            ;
        }

        FramedPosition(const Position& p, const FrameID& baseFrame) :
            Position(p), FramedMixin({.baseFrame = baseFrame})
        {
            ;
        }

        std::string
        str() const
        {
            return "Position " + FramedMixin::strTemplate();
        }
    };

} // namespace quant::position


namespace quant
{
    using core::position::FramedPosition;
} // namespace quant
