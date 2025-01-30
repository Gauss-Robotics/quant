#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/framed_geometry/forward_declarations.h>
#include <quant/framed_units/velocity/forward_declarations.h>
#include <quant/units/velocity/Twist.h>

#include <ostream>

namespace quant::framed_units::velocity
{

    class Twist : public FramedState<units::velocity::Twist>
    {
    public:
        using State::State;
    };

    std::ostream&
    operator<<(std::ostream& os, Twist const& rhs);

}  // namespace quant::framed_units::velocity
