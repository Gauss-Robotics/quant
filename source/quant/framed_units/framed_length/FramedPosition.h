#pragma once


#include <Eigen/Geometry>

#include <simox/core/length/Position.h>
#include <simox/core/length/frame/FramedMixin.h>


namespace simox::core::position
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

} // namespace simox::core::position


namespace simox
{
    using core::position::FramedPosition;
} // namespace simox
