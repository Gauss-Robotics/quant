#include <quant/framed_units/position/Position.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/units/position/AngularDisplacement.h>
#include <quant/units/position/LinearDisplacement.h>

namespace quant::framed_units::position
{

    units::position::Position
    position_basis_change(units::position::Position const& pos, framed_geometry::BaseChange const& transform)
    {
        using PositionAccessor = geometry::detail::StateAccessor<units::position::Position>;
        using AngularAccessor =
            geometry::detail::DifferenceAccessor<units::position::AngularDisplacement>;
        using LinearAccessor =
            geometry::detail::DifferenceAccessor<units::position::LinearDisplacement>;
        auto const R =
            AngularAccessor::representation(transform.transformation.angular());
        auto const t =
            LinearAccessor::representation(transform.transformation.linear());
        auto const p = PositionAccessor::representation(pos);
        return PositionAccessor::make(R.inverse() * (p - t));
    }
}  // namespace quant::framed_units::position