#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/framed_units/acceleration/forward_declarations.h>
#include <quant/units/acceleration/LinearAcceleration.h>

namespace quant::framed_units::acceleration
{

    class LinearAcceleration :
        public framed_geometry::State<units::acceleration::LinearAcceleration>
    {
    public:
        using State::State;
    };
}  // namespace quant::framed_units::acceleration
