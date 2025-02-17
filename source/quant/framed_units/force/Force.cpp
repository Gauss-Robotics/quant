#include "Force.h"
#include <quant/framed_geometry/BaseChange.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/units/force/Force.h>
#include <quant/units/position/AngularDisplacement.h>
#include <quant/geometry/detail/QuantityAccessor.h>

#include "forward_declarations.h"

namespace quant::framed_units::force
{
    units::force::Force
    base_change::force(units::force::Force const& force,
                       framed_geometry::BaseChange const& base_change)
    {
        using Angular = geometry::detail::DifferenceAccessor<units::position::AngularDisplacement>;
        using Linear = geometry::detail::StateAccessor<units::force::Force>;
        auto const R = Angular::representation(base_change.transformation.angular());
        return Linear::make(R.inverse() * Linear::representation(force));
    }

}  // namespace quant::framed_units::force
