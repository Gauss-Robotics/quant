#include "Torque.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/units/force/Force.h>
#include <quant/units/force/Wrench.h>

#include "forward_declarations.h"

namespace quant::framed_units::force
{
    units::force::Torque
    base_change::torque(units::force::Torque const& torque,
                        framed_geometry::BaseChange const& base_change)
    {
        auto const spatial_accel = base_change::wrench(
            units::force::Wrench{units::force::Force::zero(), torque}, base_change);
        return spatial_accel.angular();
    }
}  // namespace quant::framed_units::force