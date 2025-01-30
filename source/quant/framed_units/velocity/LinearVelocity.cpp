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
                                  framed_geometry::BaseChange const&)
    {
        return av;
    }

}  // namespace quant::framed_units::velocity