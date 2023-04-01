#include "Speed.h"

#include <quant/units/velocity/LinearVelocity.h>

namespace quant::units::speed
{

    Speed::Speed(quant::units::velocity::LinearVelocity const& vel) : Speed::Speed(vel.to_speed())
    {
        ;
    }

}  // namespace quant::units::speed
