#include "LinearVelocity.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/units/velocity/LinearVelocity.h>

namespace quant::framed_units::velocity
{
    std::ostream&
    operator<<(std::ostream& out, LinearVelocity const& rhs)
    {
        return out << rhs.to_string();
    }

    units::velocity::LinearVelocity
    base_change::linear_velocity(units::velocity::LinearVelocity const& av,
                                 framed_geometry::BaseChange const& bc)
    {
        using Angular = geometry::detail::DifferenceAccessor<AngularDisplacement>;
        using Linear = geometry::detail::StateAccessor<units::velocity::LinearVelocity>;
        auto const R = Angular::representation(bc.transformation.angular());
        return Linear::make(R.inverse() * Linear::representation(av));
    }

}  // namespace quant::framed_units::velocity