#pragma once

#include <quant/geometry/SE3State.h>
#include <quant/units/position/Orientation.h>
#include <quant/units/position/Position.h>
#include <quant/units/position/forward_declarations.h>

namespace quant::units::position
{

    class Pose : public geometry::SE3State<Pose>
    {
    public:
        // Construct.
        using geometry::SE3State<Pose>::SE3State;
    };

    std::ostream&
    operator<<(std::ostream& os, Pose const& rhs);

}  // namespace quant::units::position
