#include "LinearJerk.h"

namespace quant::units::jerk
{

}  // namespace quant::units::jerk

namespace quant::units
{

    std::ostream&
    jerk::operator<<(std::ostream& out, LinearJerk const& rhs)
    {
        out << rhs.to_string("LinearJerk", "mm/s³");
        return out;
    }

}  // namespace quant::units
