#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/framed_geometry/forward_declarations.h>
#include <quant/framed_units/velocity/forward_declarations.h>
#include <quant/units/velocity/AngularVelocity.h>

#include <ostream>

namespace quant::framed_units::velocity
{

    class AngularVelocity : public FramedState<units::velocity::AngularVelocity>
    {
    public:
        using State::State;
    };

    std::ostream&
    operator<<(std::ostream& os, AngularVelocity const& rhs);

}  // namespace quant::framed_units::velocity
