#include "AngularVelocity.h"


namespace quant::units::velocity
{

} // namespace quant::units::velocity


namespace quant::units
{

    std::ostream&
    velocity::operator<<(std::ostream& out, const AngularVelocity& rhs)
    {
        out << rhs.toString("AngularVelocity", "rad/s");
        return out;
    }

} // namespace quant::units
