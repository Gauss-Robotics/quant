#pragma once

#include <quant/framed_units/position/forward_declarations.h>
#include <quant/units/position/Position.h>
#include <quant/units/position/SpatialDisplacement.h>

#include <quant/framed_geometry/FramedState.h>

namespace quant::framed_units::position
{

    class Position : public framed_geometry::FramedState<units::position::Position>
    {

    public:
        using FramedState<units::position::Position>::FramedState;
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
        return PositionAccessor::make(
            AngularAccessor::representation(transform.transformation.angular()) *
                PositionAccessor::representation(pos) +
            LinearAccessor::representation(transform.transformation.linear()));
    }
}  // namespace quant::framed_units::position
