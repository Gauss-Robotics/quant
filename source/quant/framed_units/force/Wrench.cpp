#include "Wrench.h"

#include <quant/framed_geometry/Adjoint.h>
#include <quant/framed_geometry/BaseChange.h>
#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/Vector.h>
#include <quant/units/force/Torque.h>

namespace quant::framed_units::force
{

    Torque
    Wrench::angular() const
    {
        return {get_framed_object().angular(),
                {.name = get_name(), .base_frame = get_base_frame()}};
    }

    Force
    Wrench::linear() const
    {
        return {get_framed_object().linear(), {.name = get_name(), .base_frame = get_base_frame()}};
    }

    units::force::Wrench
    base_change::wrench(units::force::Wrench const& wrench,
                        framed_geometry::BaseChange const& base_change)
    {
        using SA = geometry::detail::StateAccessor<units::force::Wrench>;
        // Formula 3.98 from Modern Robotics
        // se3 = [m, f]
        auto const adj = framed_geometry::Adjoint(base_change.transformation).matrix().transpose();
        Eigen::Vector<double, 6> const w_prime = adj * SA::representation(wrench);
        return SA::make(w_prime);
    }
}  // namespace quant::framed_units::force