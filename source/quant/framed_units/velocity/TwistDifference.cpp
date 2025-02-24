#include "TwistDifference.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/units/velocity/TwistDifference.h>

namespace quant::framed_units::velocity
{
    units::velocity::TwistDifference
    base_change::twist_difference(units::velocity::TwistDifference const& /*av*/,
                                  BaseChange const&)
    {
        throw std::runtime_error("Not implemented");
    }

}  // namespace quant::framed_units::velocity