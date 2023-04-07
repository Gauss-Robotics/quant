#include "LinearVelocity.h"

#include <quant/units/position/LinearDisplacement.h>

namespace quant::units::velocity
{

}  // namespace quant::units::velocity

namespace quant
{

    LinearVelocity
    operator/(LinearDisplacement const& dx, Duration const& dt)
    {
        return LinearVelocity::millimeters_per_second(dx.to_millimeters() / dt.to_seconds());
    }

}  // namespace quant
