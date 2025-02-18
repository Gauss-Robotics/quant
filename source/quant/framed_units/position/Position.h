#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/framed_units/position/forward_declarations.h>
#include <quant/units/position/Position.h>

namespace quant::framed_units::position
{

    class Position : public framed_geometry::State<units::position::Position>
    {
    public:
        using State::State;
    };
}  // namespace quant::framed_units::position
