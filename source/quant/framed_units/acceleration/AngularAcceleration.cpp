#include "AngularAcceleration.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/units/acceleration/AngularAcceleration.h>
#include <quant/units/acceleration/LinearAcceleration.h>
#include <quant/units/acceleration/SpatialAcceleration.h>

#include "forward_declarations.h"

namespace quant::framed_units::acceleration
{
    units::acceleration::AngularAcceleration
    base_change::angular_acceleration(
        units::acceleration::AngularAcceleration const& angular_acceleration,
        framed_geometry::BaseChange const& base_change)
    {
        const auto spatial_accel = base_change::spatial_acceleration(
            units::acceleration::SpatialAcceleration{
                units::acceleration::LinearAcceleration::zero(), angular_acceleration},
            base_change);
        return spatial_accel.angular();
    }
}  // namespace quant::framed_units::acceleration