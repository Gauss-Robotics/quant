#include "AngularAcceleration.h"

namespace quant::units::acceleration
{

}  // namespace quant::units::acceleration

namespace quant::units
{

    std::ostream&
    acceleration::operator<<(std::ostream& out, AngularAcceleration const& rhs)
    {
        out << rhs.to_string("AngularAcceleration", "rad/s²");
        return out;
    }

}  // namespace quant::units
