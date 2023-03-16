#include "AngularAcceleration.h"


namespace quant::units::acceleration
{

} // namespace quant::units::acceleration


namespace quant::units
{

    std::ostream&
    acceleration::operator<<(std::ostream& out, const AngularAcceleration& rhs)
    {
        out << rhs.toString("AngularAcceleration", "rad/s²");
        return out;
    }

} // namespace quant::units
