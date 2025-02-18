#include "Wrench.h"

namespace quant::units::force
{

    std::ostream&
    operator<<(std::ostream& out, Wrench const& rhs)
    {
        return out << rhs.to_string();
    }
}  // namespace quant::units::force