#pragma once

#include <quant/geometry/SpatialIsometricState.h>
#include <quant/units/position/forward_declarations.h>
#include <quant/units/position/Position.h>
#include <quant/units/position/Orientation.h>

namespace quant::units::position
{

    class Pose : public geometry::SpatialIsometricState<Pose>
    {
    public:
        // Construct.
        using geometry::SpatialIsometricState<Pose>::SpatialIsometricState;
    };

    std::ostream&
    operator<<(std::ostream& os, Pose const& rhs);

}  // namespace quant::units::position
