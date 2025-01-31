#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/framed_units/position/forward_declarations.h>
#include <quant/units/position/Pose.h>

namespace quant::framed_units::position
{
    class Pose : public framed_geometry::State<units::position::Pose>
    {
    public:
        using State::State;
    };

    std::ostream&
    operator<<(std::ostream& os, Pose const& rhs);

}  // namespace quant::framed_units::position
