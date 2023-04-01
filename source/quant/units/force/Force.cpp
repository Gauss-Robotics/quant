#include "Force.h"

namespace quant::units::force
{

}  // namespace quant::units::force

namespace quant::units
{

    std::ostream&
    force::operator<<(std::ostream& out, Force const& rhs)
    {
        out << rhs.to_string("Force", "N");
        return out;
    }

}  // namespace quant::units
