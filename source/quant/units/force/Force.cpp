#include "Force.h"


namespace quant::units::force
{

} // namespace quant::units::force


namespace quant::units
{

    std::ostream&
    force::operator<<(std::ostream& out, const Force& rhs)
    {
        out << rhs.toString("Force", "N");
        return out;
    }

} // namespace quant::units
