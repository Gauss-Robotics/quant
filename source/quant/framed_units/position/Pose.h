#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/framed_units/position/forward_declarations.h>
#include <quant/units/position/Pose.h>

namespace quant::framed_units::position
{
    class Pose : public framed_geometry::State<units::position::Pose>
    {
    public:
        Orientation
        angular() const;

        Position
        linear() const;
        using State::State;
    };
}  // namespace quant::framed_units::position
