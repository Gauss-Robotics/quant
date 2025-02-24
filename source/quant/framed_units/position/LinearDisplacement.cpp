#include "LinearDisplacement.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/units/position/LinearDisplacement.h>
#include <quant/units/position/SpatialDisplacement.h>

namespace quant::framed_units::position
{

    units::position::LinearDisplacement
    ld_basis_change(units::position::LinearDisplacement const& ld,
                    framed_geometry::BaseChange const& transform)
    {
        // differences of positions are always in the global frame
        using LDAccessor = geometry::detail::DifferenceAccessor<quant::LinearDisplacement>;
        using TransformAccessor =
            geometry::detail::DifferenceAccessor<units::position::SpatialDisplacement>;
        auto const R = TransformAccessor::representation(transform.transformation);
        return LDAccessor::make(
            Eigen::Translation3d((R.inverse() * LDAccessor::representation(ld) * R).translation()));
    }
}  // namespace quant::framed_units::position