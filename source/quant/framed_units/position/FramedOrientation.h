#pragma once

#include <quant/framed_geometry/FramedState.h>
#include <quant/framed_units/position/forward_declarations.h>
#include <quant/units/position/Orientation.h>
#include <quant/units/position/SpatialDisplacement.h>

namespace quant::framed_units::position
{
    inline units::position::Orientation
    orientation_basis_change(units::position::Orientation const& orientation,
                             framed_geometry::BaseChange const& transform)
    {
        using OrientationAccessor = geometry::detail::StateAccessor<units::position::Orientation>;
        using TransformAccessor =
            geometry::detail::DifferenceAccessor<units::position::AngularDisplacement>;
        return OrientationAccessor::make(
            TransformAccessor::representation(transform.transformation.angular()) *
            OrientationAccessor::representation(orientation));
    }

    class  Orientation : public FramedState<units::position:: Orientation>
    {
    public:
        using FramedState::FramedState;
    };

    inline std::ostream&
    operator<<(std::ostream& os, Orientation const& rhs)
    {
        return os << rhs.to_string();
    }

}  // namespace quant::framed_units::position
