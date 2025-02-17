#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/units/force/Force.h>

namespace quant::framed_units::force
{

    class Force : public framed_geometry::State<units::force::Force>
    {
    public:
        using State::State;
    };
}  // namespace quant::framed_units::force
