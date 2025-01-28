#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/framed_units/position/forward_declarations.h>
#include <quant/units/position/Position.h>
#include <quant/units/position/SpatialDisplacement.h>

namespace quant::framed_units::position
{

    class Position : public FramedState<units::position::Position>
    {
    public:
        using State::State;
    };

    inline units::position::Position
    position_basis_change(units::position::Position const& pos,
                          framed_geometry::BaseChange const& transform)
    {
        using PositionAccessor = geometry::detail::StateAccessor<units::position::Position>;
        using AngularAccessor =
            geometry::detail::DifferenceAccessor<units::position::AngularDisplacement>;
        using LinearAccessor =
            geometry::detail::DifferenceAccessor<units::position::LinearDisplacement>;
        auto const R = AngularAccessor::representation(transform.transformation.angular());
        auto const t = LinearAccessor::representation(transform.transformation.linear());
        auto const p = PositionAccessor::representation(pos);
        return PositionAccessor::make(R.inverse() * (p - t));
    }
}  // namespace quant::framed_units::position
