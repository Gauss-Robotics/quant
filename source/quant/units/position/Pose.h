#pragma once

#include <quant/geometry/SpatialIsometricState.h>
#include <quant/units/position_fwd.h>

namespace quant::units::position
{

    class Pose : public geometry::SpatialIsometricState<Pose>
    {
        // Construct.
    public:
        using geometry::SpatialIsometricState<Pose>::SpatialIsometricState;

        using DifferenceType = SpatialDisplacement;
    };

}  // namespace quant::units::position
