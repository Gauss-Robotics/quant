#include "AngularVelocity.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/units/velocity/AngularVelocity.h>

namespace quant::framed_units::velocity
{
    std::ostream&
    operator<<(std::ostream& out, AngularVelocity const& rhs)
    {
        return out << rhs.to_string();
    }

    units::velocity::AngularVelocity
    base_change::angular_velocity(units::velocity::AngularVelocity const& av,
                                  framed_geometry::BaseChange const&)
    {
        return av;
    }

}  // namespace quant::framed_units::velocity