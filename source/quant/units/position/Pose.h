#pragma once

#include <quant/geometry/IsometryQuantity.h>
#include <quant/units/position_fwd.h>

namespace quant::units::position
{

    class Pose : public geometry::IsometryQuantity<Pose>
    {
        // Construct.
    public:
        using geometry::IsometryQuantity<Pose>::IsometryQuantity;
    };

}  // namespace quant::units::position

namespace quant
{
    using units::position::Pose;
}  // namespace quant
