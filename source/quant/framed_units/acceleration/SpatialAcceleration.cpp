#include "SpatialAcceleration.h"

#include <quant/framed_units/acceleration/LinearAcceleration.h>

#include "forward_declarations.h"

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

    std::ostream&
    operator<<(std::ostream& out, SpatialAcceleration const& rhs)
    {
        return out << rhs.to_string();
    }

    units::acceleration::SpatialAcceleration
    base_change::spatial_acceleration(
        units::acceleration::SpatialAcceleration const& spatial_acceleration,
        framed_geometry::BaseChange const& base_change)
    {
        throw std::runtime_error("Not implemented");
    }
}  // namespace quant::framed_units::acceleration