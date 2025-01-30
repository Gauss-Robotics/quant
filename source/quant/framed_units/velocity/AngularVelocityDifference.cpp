#include "AngularVelocityDifference.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/units/velocity/AngularVelocityDifference.h>

namespace quant::framed_units::velocity
{
    std::ostream&
    operator<<(std::ostream& out, AngularVelocityDifference const& rhs)
    {
        return out << rhs.to_string();
    }

    units::velocity::AngularVelocityDifference
    base_change::angular_velocity_difference(units::velocity::AngularVelocityDifference const& av,
                                  framed_geometry::BaseChange const&)
    {
        return av;
    }

}  // namespace quant::framed_units::velocity