#include "SpatialAcceleration.h"

#include <quant/framed_units/acceleration/LinearAcceleration.h>
#include <quant/units/acceleration/AngularAcceleration.h>
#include <quant/units/acceleration/LinearAcceleration.h>

#include "forward_declarations.h"
#include "quant/framed_geometry/Adjoint.h"

namespace quant::framed_units::acceleration
{

    AngularAcceleration
    SpatialAcceleration::angular() const
    {
        return AngularAcceleration{get_framed_object().angular(),
                                   {.name = get_name(), .base_frame = get_base_frame()}};
    }

    LinearAcceleration
    SpatialAcceleration::linear() const
    {
        return LinearAcceleration{get_framed_object().linear(),
                                  {.name = get_name(), .base_frame = get_base_frame()}};
    }

    units::acceleration::SpatialAcceleration
    base_change::spatial_acceleration(
        units::acceleration::SpatialAcceleration const& spatial_acceleration,
        framed_geometry::BaseChange const& base_change)
    {
        using SA = geometry::detail::StateAccessor<units::acceleration::SpatialAcceleration>;
        // Formula 3.98 from Modern Robotics
        framed_geometry::Adjoint const adjoint{base_change.transformation};
        return SA::make(adjoint.matrix().transpose() * SA::representation(spatial_acceleration));
    };
}  // namespace quant::framed_units::acceleration