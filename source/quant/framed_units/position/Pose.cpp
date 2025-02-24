#include "Pose.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/framed_units/position/Position.h>
#include <quant/framed_units/position/Orientation.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/units/position/Pose.h>
#include <quant/units/position/SpatialDisplacement.h>

namespace quant::framed_units::position
{

    units::position::Pose
    pose_basis_change(units::position::Pose const& pose,
                      framed_geometry::BaseChange const& transform)
    {
        using PoseAccessor = geometry::detail::StateAccessor<units::position::Pose>;
        using TransformAccessor =
            geometry::detail::DifferenceAccessor<units::position::SpatialDisplacement>;
        auto const T = TransformAccessor::representation(transform.transformation);
        auto const P = PoseAccessor::representation(pose);
        return PoseAccessor::make(T.inverse() * P);
    }

    Orientation
    Pose::angular() const
    {
        return {get_framed_object().angular(),
                {.name = get_name(), .base_frame = get_base_frame()}};
    }

    Position
    Pose::linear() const
    {
        return {get_framed_object().linear(), {.name = get_name(), .base_frame = get_base_frame()}};
    }
}  // namespace quant::framed_units::position