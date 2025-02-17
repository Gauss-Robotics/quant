#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/framed_units/acceleration/forward_declarations.h>
#include <quant/units/acceleration/AngularAcceleration.h>

namespace quant::framed_units::acceleration
{

    class AngularAcceleration :
        public framed_geometry::State<units::acceleration::AngularAcceleration>
    {
    public:
        using State::State;
    };
}  // namespace quant::framed_units::acceleration
