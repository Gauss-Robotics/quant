#include "LinearJerk.h"


namespace quant::units::jerk
{

} // namespace quant::units::jerk


namespace quant::units
{

    std::ostream&
    jerk::operator<<(std::ostream& out, const LinearJerk& rhs)
    {
        out << rhs.toString("LinearJerk", "mm/s³");
        return out;
    }

} // namespace quant::units
