#include "Torque.h"

#include "forward_declarations.h"

namespace quant::framed_units::force
{
    std::ostream&
    operator<<(std::ostream& out, Torque const& rhs)
    {
        return out << rhs.to_string();
    }

    units::force::Torque
    base_change::torque(units::force::Torque const& torque,
                        framed_geometry::BaseChange const& base_change)
    {
        throw std::runtime_error("Not implemented");
    }
}  // namespace quant::framed_units::force