#include "LinearVelocity.h"

namespace quant::units::velocity
{

}  // namespace quant::units::velocity

namespace quant::units
{

    velocity::LinearVelocity
    position::operator/(LinearDisplacement const& dx, Duration const& dt)
    {
        return velocity::LinearVelocity::millimeters_per_second(dx.to_millimeters() /
                                                                dt.to_seconds());
    }

}  // namespace quant::units
