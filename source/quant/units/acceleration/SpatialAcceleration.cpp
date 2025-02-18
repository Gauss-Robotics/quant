#include "SpatialAcceleration.h"

namespace quant::units::acceleration
{

    std::ostream&
    operator<<(std::ostream& out, SpatialAcceleration const& rhs)
    {
        return out << rhs.to_string();
    }
}  // namespace quant::units::acceleration