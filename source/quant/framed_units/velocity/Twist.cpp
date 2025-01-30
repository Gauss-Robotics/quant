#include "Twist.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/units/velocity/Twist.h>

namespace quant::framed_units::velocity
{
    std::ostream&
    operator<<(std::ostream& out, Twist const& rhs)
    {
        return out << rhs.to_string();
    }

    units::velocity::Twist
    base_change::twist(units::velocity::Twist const& av,
                                  framed_geometry::BaseChange const&)
    {
        return av;
    }

}  // namespace quant::framed_units::velocity