#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/framed_units/position/forward_declarations.h>
#include <quant/units/position/Pose.h>
#include <quant/units/position/SpatialDisplacement.h>


namespace quant::framed_units::position
{
    inline units::position::Pose
    pose_basis_change(units::position::Pose const& pose,
                    framed_geometry::BaseChange const& transform)
    {
        // Corresponds to the left + operator and is NOT the same as pose + transform, because here
        // the transform is in the "global" or base frame
        using PoseAccessor = geometry::detail::StateAccessor<units::position::Pose>;
        using TransformAccessor = geometry::detail::DifferenceAccessor<units::position::SpatialDisplacement>;
        return PoseAccessor::make(
            TransformAccessor::representation(transform.transformation) *
            PoseAccessor::representation(pose));
    }

    class Pose : public Framed<units::position::Pose>
    {
    public:
        using Framed<units::position::Pose>::Framed;
    };

    inline std::ostream&
    operator<<(std::ostream& os, framed_units::position::Pose const& rhs)
    {
        return os << rhs.to_string();
    }

}  // namespace quant::framed_units::position
