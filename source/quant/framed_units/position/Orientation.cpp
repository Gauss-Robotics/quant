#include "Orientation.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/units/position/Orientation.h>

namespace quant::framed_units::position
{

    units::position::Orientation
    orientation_basis_change(units::position::Orientation const& orientation,
                             framed_geometry::BaseChange const& transform)
    {
        using OrientationAccessor = geometry::detail::StateAccessor<units::position::Orientation>;
        using TransformAccessor =
            geometry::detail::DifferenceAccessor<units::position::AngularDisplacement>;
        auto const R = TransformAccessor::representation(transform.transformation.angular());
        auto const o = OrientationAccessor::representation(orientation);
        return OrientationAccessor::make(R.inverse() * o);
    }
}  // namespace quant::framed_units::position