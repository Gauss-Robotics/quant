#include "AngularVelocity.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/units/position/AngularDisplacement.h>
#include <quant/units/velocity/AngularVelocity.h>

namespace quant::framed_units::velocity
{
    std::ostream&
    operator<<(std::ostream& out, AngularVelocity const& rhs)
    {
        return out << rhs.to_string();
    }

    units::velocity::AngularVelocity
    base_change::angular_velocity(units::velocity::AngularVelocity const& av,
                                  framed_geometry::BaseChange const& bc)
    {
        using Position = geometry::detail::DifferenceAccessor<units::position::AngularDisplacement>;
        using Velocity = geometry::detail::StateAccessor<units::velocity::AngularVelocity>;
        const auto R = Position::representation(bc.transformation.angular());
        const auto omega = Velocity::representation(av);
        // TODO: this discards angles greater 360 degrees
        return Velocity::make(static_cast<Eigen::AngleAxisd>(
             R.inverse() * omega * R));
    }

}  // namespace quant::framed_units::velocity