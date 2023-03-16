#pragma once


#include <Eigen/Geometry>

#include <simox/core/geometry/IsometryQuantity.h>
#include <simox/core/units/position/forward_declarations.h>


namespace simox::core::units::position
{

    class Pose : public geometry::IsometryQuantity<Pose>
    {
        // Construct.
    public:
        using geometry::IsometryQuantity<Pose>::IsometryQuantity;

    protected:
        friend class Transform;
    };

} // namespace simox::core::units::position


namespace simox
{
    using core::units::position::Pose;
} // namespace simox
