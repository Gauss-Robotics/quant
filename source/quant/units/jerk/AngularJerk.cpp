#include "AngularJerk.h"

namespace quant::units::jerk
{

}  // namespace quant::units::jerk

namespace quant::units
{

    std::ostream&
    jerk::operator<<(std::ostream& out, AngularJerk const& rhs)
    {
        out << rhs.to_string("AngularJerk", "rad/s³");
        return out;
    }

}  // namespace quant::units
