#include "SpatialAccelerationDifference.h"

#include "forward_declarations.h"

namespace quant::framed_units::acceleration
{
    units::acceleration::SpatialAccelerationDifference
    base_change::spatial_acceleration_difference(
        units::acceleration::SpatialAccelerationDifference const& spatial_acceleration_difference,
        framed_geometry::BaseChange const& base_change)
    {
        throw std::runtime_error("Not implemented");
    }
}  // namespace quant::framed_units::acceleration