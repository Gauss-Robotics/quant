#include "AngularVelocityDifference.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/units/velocity/AngularVelocityDifference.h>

namespace quant::framed_units::velocity
{
    units::velocity::AngularVelocityDifference
    base_change::angular_velocity_difference(units::velocity::AngularVelocityDifference const& /*av*/,
                                             BaseChange const&)
    {
        throw std::runtime_error("Not implemented");
    }

}  // namespace quant::framed_units::velocity