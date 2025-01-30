#include "TwistDifference.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/units/velocity/TwistDifference.h>

namespace quant::framed_units::velocity
{
    std::ostream&
    operator<<(std::ostream& out, TwistDifference const& rhs)
    {
        return out << rhs.to_string();
    }

    units::velocity::TwistDifference
    base_change::twist_difference(units::velocity::TwistDifference const& av,
                                  framed_geometry::BaseChange const&)
    {
        return av;
    }

}  // namespace quant::framed_units::velocity