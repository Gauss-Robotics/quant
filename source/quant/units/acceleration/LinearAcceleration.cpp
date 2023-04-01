#include "LinearAcceleration.h"

namespace quant::units::acceleration
{

}  // namespace quant::units::acceleration

namespace quant::units
{

    std::ostream&
    acceleration::operator<<(std::ostream& out, LinearAcceleration const& rhs)
    {
        out << rhs.to_string("LinearAcceleration", "mm/s²");
        return out;
    }

}  // namespace quant::units
