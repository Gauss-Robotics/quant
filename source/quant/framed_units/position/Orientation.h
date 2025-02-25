#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/framed_units/position/forward_declarations.h>
#include <quant/units/position/Orientation.h>

namespace quant::framed_units::position
{
    class Orientation : public FramedState<units::position::Orientation>
    {
    public:
        using State::State;
    };
}  // namespace quant::framed_units::position