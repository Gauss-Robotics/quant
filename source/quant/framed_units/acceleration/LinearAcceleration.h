#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/units/acceleration/LinearAcceleration.h>

#include <ostream>

namespace quant::framed_units::acceleration
{

    class LinearAcceleration :
        public framed_geometry::State<units::acceleration::LinearAcceleration>
    {
    public:
        using State::State;
    };
}  // namespace quant::framed_units::acceleration
