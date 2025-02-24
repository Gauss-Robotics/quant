#include "LinearVelocityDifference.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/units/velocity/LinearVelocityDifference.h>

namespace quant::framed_units::velocity
{


    units::velocity::LinearVelocityDifference
    base_change::linear_velocity_difference(units::velocity::LinearVelocityDifference const& /*av*/,
                                  BaseChange const&)
    {
        throw std::runtime_error("Not implemented");
    }

}  // namespace quant::framed_units::velocity