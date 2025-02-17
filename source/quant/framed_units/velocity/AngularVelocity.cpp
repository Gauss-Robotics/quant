#include "AngularVelocity.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/units/position/AngularDisplacement.h>
#include <quant/units/velocity/AngularVelocity.h>

namespace quant::framed_units::velocity
{
    units::velocity::AngularVelocity
    base_change::angular_velocity(units::velocity::AngularVelocity const& av,
                                  framed_geometry::BaseChange const& bc)
    {
        using Position = geometry::detail::DifferenceAccessor<units::position::AngularDisplacement>;
        using Velocity = geometry::detail::StateAccessor<units::velocity::AngularVelocity>;
        auto const R = Position::representation(bc.transformation.angular());
        auto const omega = Velocity::representation(av);
        return Velocity::make(R.inverse() * omega);
    }

}  // namespace quant::framed_units::velocity