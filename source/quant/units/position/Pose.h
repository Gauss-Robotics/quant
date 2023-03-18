#pragma once


#include <quant/geometry/IsometryQuantity.h>
#include <quant/units/position_fwd.h>

#include <Eigen/Geometry>

namespace quant::units::position
{

    class Pose : public geometry::IsometryQuantity<Pose>
    {
        // Construct.
    public:
        using geometry::IsometryQuantity<Pose>::IsometryQuantity;

    protected:
        friend class Transform;
    };

}  // namespace quant::units::position

namespace quant
{
    using units::position::Pose;
}  // namespace quant
