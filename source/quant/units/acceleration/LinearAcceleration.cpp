#include "LinearAcceleration.h"


namespace quant::units::acceleration
{

} // namespace quant::units::acceleration


namespace quant::units
{

    std::ostream&
    acceleration::operator<<(std::ostream& out, const LinearAcceleration& rhs)
    {
        out << rhs.toString("LinearAcceleration", "mm/s²");
        return out;
    }

} // namespace quant::units
