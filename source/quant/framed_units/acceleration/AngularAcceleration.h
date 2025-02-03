#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/units/acceleration/AngularAcceleration.h>

#include <ostream>

namespace quant::framed_units::acceleration
{

    class AngularAcceleration :
        public framed_geometry::State<units::acceleration::AngularAcceleration>
    {
    public:
        using State::State;
    };

    std::ostream&
    operator<<(std::ostream& out, AngularAcceleration const& rhs);

}  // namespace quant::framed_units::acceleration
