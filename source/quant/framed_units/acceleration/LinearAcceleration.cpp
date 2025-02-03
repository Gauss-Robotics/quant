#include "LinearAcceleration.h"

#include "forward_declarations.h"

namespace quant::framed_units::acceleration
{
    std::ostream&
    operator<<(std::ostream& os, LinearAcceleration const& rhs)
    {
        return os << rhs.to_string();
    }

    units::acceleration::LinearAcceleration
    base_change::linear_acceleration(
        units::acceleration::LinearAcceleration const& linear_acceleration,
        framed_geometry::BaseChange const& base_change)
    {
        throw std::runtime_error("Not implemented");
    }
}  // namespace quant::framed_units::acceleration
