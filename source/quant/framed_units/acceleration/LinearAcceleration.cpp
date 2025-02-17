#include "LinearAcceleration.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/units/acceleration/LinearAcceleration.h>
#include <quant/units/position/AngularDisplacement.h>

#include "forward_declarations.h"

namespace quant::framed_units::acceleration
{
    units::acceleration::LinearAcceleration
    base_change::linear_acceleration(
        units::acceleration::LinearAcceleration const& linear_acceleration,
        framed_geometry::BaseChange const& base_change)
    {
        using Angular = geometry::detail::DifferenceAccessor<units::position::AngularDisplacement>;
        using Linear = geometry::detail::StateAccessor<units::acceleration::LinearAcceleration>;
        auto const R = Angular::representation(base_change.transformation.angular());
        return Linear::make(R.inverse() * Linear::representation(linear_acceleration));
    }
}  // namespace quant::framed_units::acceleration
