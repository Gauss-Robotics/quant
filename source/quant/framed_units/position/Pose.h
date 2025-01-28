#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/framed_units/position/forward_declarations.h>
#include <quant/units/position/Pose.h>
#include <quant/units/position/SpatialDisplacement.h>

namespace quant::framed_units::position
{
    inline units::position::Pose
    pose_basis_change(units::position::Pose const& pose,
                      framed_geometry::BaseChange const& transform)
    {
        using PoseAccessor = geometry::detail::StateAccessor<units::position::Pose>;
        using TransformAccessor =
            geometry::detail::DifferenceAccessor<units::position::SpatialDisplacement>;
        auto const T = TransformAccessor::representation(transform.transformation);
        const auto P = PoseAccessor::representation(pose);
        return PoseAccessor::make(T.inverse() * P);
    }

    class Pose : public FramedState<units::position::Pose>
    {
    public:
        using State::State;
    };

    inline std::ostream&
    operator<<(std::ostream& os, Pose const& rhs)
    {
        return os << rhs.to_string();
    }

}  // namespace quant::framed_units::position
