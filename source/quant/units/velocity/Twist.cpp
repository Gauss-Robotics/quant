#include "Twist.h"

namespace quant::units::velocity
{
    std::ostream&
    operator<<(std::ostream& os, Twist const& rhs)
    {
        return os << rhs.to_string();
    }
}  // namespace quant::units::velocity