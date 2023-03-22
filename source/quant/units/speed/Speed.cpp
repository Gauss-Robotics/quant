#include "Speed.h"

#include <quant/units/velocity/LinearVelocity.h>

namespace quant::units::speed
{

    Speed::Speed(quant::units::velocity::LinearVelocity const& vel) : Speed::Speed(vel.toSpeed())
    {
        ;
    }

}  // namespace quant::units::speed
