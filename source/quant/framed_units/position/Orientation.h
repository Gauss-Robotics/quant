#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/framed_units/position/forward_declarations.h>
#include <quant/units/position/Orientation.h>
#include <quant/units/position/SpatialDisplacement.h>

#include <doctest/doctest.h>

namespace quant::framed_units::position
{
    inline units::position::Orientation
    orientation_basis_change(units::position::Orientation const& orientation,
                             BaseChange const& transform)
    {
        using OrientationAccessor = geometry::detail::StateAccessor<units::position::Orientation>;
        using TransformAccessor =
            geometry::detail::DifferenceAccessor<units::position::AngularDisplacement>;
        auto const R = TransformAccessor::representation(transform.transformation.angular());
        auto const o = OrientationAccessor::representation(orientation);
        return OrientationAccessor::make(R.inverse() * o);
    }

    class Orientation : public FramedState<units::position::Orientation>
    {
    public:
        using State::State;
    };

    inline std::ostream&
    operator<<(std::ostream& os, Orientation const& rhs)
    {
        return os << rhs.to_string();
    }

}  // namespace quant::framed_units::position