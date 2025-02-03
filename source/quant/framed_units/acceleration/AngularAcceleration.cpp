#include "AngularAcceleration.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/units/acceleration/AngularAcceleration.h>

#include "forward_declarations.h"

namespace quant::framed_units::acceleration
{

    std::ostream&
    operator<<(std::ostream& out, AngularAcceleration const& rhs)
    {
        return out << rhs.to_string();
    }

    units::acceleration::AngularAcceleration
    base_change::angular_acceleration(
        units::acceleration::AngularAcceleration const& angular_acceleration,
        framed_geometry::BaseChange const& base_change)
    {
        throw std::runtime_error("Not implemented");
    }
}  // namespace quant::framed_units::acceleration