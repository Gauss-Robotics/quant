#include "Torque.h"

namespace quant::units::force
{

}  // namespace quant::units::force

namespace quant::units
{

    std::ostream&
    force::operator<<(std::ostream& out, Torque const& rhs)
    {
        out << rhs.to_string("Torque", "Nm");
        return out;
    }

}  // namespace quant::units
