#include "AngularJerk.h"


namespace quant::units::jerk
{

} // namespace quant::units::jerk


namespace quant::units
{

    std::ostream&
    jerk::operator<<(std::ostream& out, const AngularJerk& rhs)
    {
        out << rhs.toString("AngularJerk", "rad/s³");
        return out;
    }

} // namespace quant::units
