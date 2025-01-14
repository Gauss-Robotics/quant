#pragma once

#include <quant/geometry/SpatialIsometricState.h>
#include <quant/units/position/forward_declarations.h>

namespace quant::units::position
{

    class Pose : public geometry::SpatialIsometricState<Pose>
    {
        // Construct.
    public:
        using geometry::SpatialIsometricState<Pose>::SpatialIsometricState;
    };

}  // namespace quant::units::position
