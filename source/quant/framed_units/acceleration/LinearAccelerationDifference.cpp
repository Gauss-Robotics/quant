#include "LinearAccelerationDifference.h"

#include <quant/units/acceleration/LinearAcceleration.h>

#include "forward_declarations.h"

namespace quant::framed_units::acceleration
{
    units::acceleration::LinearAccelerationDifference
    base_change::linear_acceleration_difference(
        units::acceleration::LinearAccelerationDifference const& linear_acceleration_difference,
        framed_geometry::BaseChange const& base_change)
    {
        throw std::runtime_error("Not implemented");
    }
}  // namespace quant::framed_units::acceleration