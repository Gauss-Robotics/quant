#include "WrenchDifference.h"

namespace quant::units::force
    {
    std::ostream&
    operator<<(std::ostream& out, WrenchDifference const& rhs)
    {
        return out << rhs.to_string();
    }
}  // namespace quant::units::force