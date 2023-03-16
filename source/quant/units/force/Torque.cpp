#include "Torque.h"


namespace quant::units::force
{

} // namespace quant::units::force


namespace quant::units
{

    std::ostream&
    force::operator<<(std::ostream& out, const Torque& rhs)
    {
        out << rhs.toString("Torque", "Nm");
        return out;
    }

} // namespace quant::units
