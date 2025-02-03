#include "ForceDifference.h"

#include "forward_declarations.h"

namespace quant::framed_units::force
{
    std::ostream&
    operator<<(std::ostream& os, ForceDifference const& rhs)
    {
        return os << rhs.to_string();
    }

    units::force::ForceDifference
    base_change::force_difference(units::force::ForceDifference const& force_difference,
                                  framed_geometry::BaseChange const& base_change)
    {
        throw std::runtime_error("Not implemented");
    }
}  // namespace quant::framed_units::force
