#include <quant/framed_units/position/Position.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>

namespace quant::framed_units::position
{

    units::position::Position
    position_basis_change(units::position::Position const& pos,
                          framed_geometry::BaseChange const& transform)
    {
        using PositionAccessor = geometry::detail::StateAccessor<units::position::Position>;
        using TransformAccessor =
            geometry::detail::DifferenceAccessor<units::position::SpatialDisplacement>;
        auto const R = TransformAccessor::representation(transform.transformation);

        auto const p = PositionAccessor::representation(pos);
        return PositionAccessor::make(Eigen::Translation3d((R.inverse() * p).translation()));
    }
}  // namespace quant::framed_units::position