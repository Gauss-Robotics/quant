#include "AngularVelocity.h"

namespace quant::units::velocity
{

}  // namespace quant::units::velocity

namespace quant::units
{

    std::ostream&
    velocity::operator<<(std::ostream& out, AngularVelocity const& rhs)
    {
        out << rhs.to_string("AngularVelocity", "rad/s");
        return out;
    }

}  // namespace quant::units
