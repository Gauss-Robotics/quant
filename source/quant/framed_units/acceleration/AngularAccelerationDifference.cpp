#include "AngularAccelerationDifference.h"

#include "forward_declarations.h"
#include "quant/units/acceleration/AngularAccelerationDifference.h"

namespace quant::framed_units::acceleration
{
    units::acceleration::AngularAccelerationDifference
    base_change::angular_acceleration_difference(
        units::acceleration::AngularAccelerationDifference const& angular_acceleration_difference,
        framed_geometry::BaseChange const& base_change)
    {
        throw std::runtime_error("Not implemented");
    }
}  // namespace quant::framed_units::acceleration