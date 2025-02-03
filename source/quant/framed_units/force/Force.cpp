#include "Force.h"

#include "forward_declarations.h"

namespace quant::framed_units::force
{
    std::ostream&
    operator<<(std::ostream& os, Force const& rhs)
    {
        return os << rhs.to_string();
    }

    units::force::Force
    base_change::force(units::force::Force const& force,
                       framed_geometry::BaseChange const& base_change)
    {
        throw std::runtime_error("Not implemented");
    }

}  // namespace quant::framed_units::force
