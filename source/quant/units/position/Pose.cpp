#include "Pose.h"


namespace quant::units::position
{

    std::ostream&
    operator<<(std::ostream& os, Pose const& rhs)
    {
        return os << rhs.to_string();
    }
} // namespace quant::units::position
