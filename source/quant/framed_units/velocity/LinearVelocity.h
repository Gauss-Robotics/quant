#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/framed_geometry/forward_declarations.h>
#include <quant/framed_units/velocity/forward_declarations.h>
#include <quant/units/velocity/LinearVelocity.h>

#include <ostream>

namespace quant::framed_units::velocity
{

    class LinearVelocity : public FramedState<units::velocity::LinearVelocity>
    {
    public:
        using State::State;
    };
}  // namespace quant::framed_units::velocity
