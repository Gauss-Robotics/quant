#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/units/force/Torque.h>
#include <quant/framed_units/force/forward_declarations.h>

namespace quant::framed_units::force
{

    class Torque : public framed_geometry::State<units::force::Torque>
    {
    public:
        using State::State;
    };
}  // namespace quant::framed_units::force
