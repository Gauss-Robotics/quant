#include "LinearVelocityDifference.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/units/velocity/LinearVelocityDifference.h>

namespace quant::framed_units::velocity
{
    std::ostream&
    operator<<(std::ostream& out, LinearVelocityDifference const& rhs)
    {
        return out << rhs.to_string();
    }

    units::velocity::LinearVelocityDifference
    base_change::linear_velocity_difference(units::velocity::LinearVelocityDifference const& av,
                                  framed_geometry::BaseChange const&)
    {
        return av;
    }

}  // namespace quant::framed_units::velocity