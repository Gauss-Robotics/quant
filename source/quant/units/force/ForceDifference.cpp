#include "ForceDifference.h"

namespace quant::units::force
{
    std::ostream&
    operator<<(std::ostream& os, ForceDifference const& rhs)
    {
        return os << rhs.to_string();
    }
}  // namespace quant::units::force
