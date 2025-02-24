#include "TorqueDifference.h"

#include "forward_declarations.h"

namespace quant::framed_units::force
{
    units::force::TorqueDifference
    base_change::torque_difference(units::force::TorqueDifference const& torque_difference,
                                   framed_geometry::BaseChange const& base_change)
    {
        throw std::runtime_error("Not implemented");
    }
}  // namespace quant::framed_units::force