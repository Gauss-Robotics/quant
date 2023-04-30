#pragma once

#include <quant/geometry/AngularState.h>
#include <quant/units/AxisAngle.h>
#include <quant/units/velocity/constants.h>
#include <quant/units/velocity_fwd.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::velocity
{

    class AngularVelocity : public geometry::AngularState<AngularVelocity>
    {
    public:
        static AngularVelocity
        radians_per_second(geometry::AxisAngle const& aa)
        {
            return {aa};
        }

        // Convert.

        AxisAngle
        to_radians_per_second() const
        {
            return {to_axis_angle(),
                    constants::names::angular_velocity,
                    constants::symbols::radians_per_second};
        }

        using geometry::AngularState<AngularVelocity>::AngularState;
    };

    inline std::ostream&
    operator<<(std::ostream& out, AngularVelocity const& rhs)
    {
        return out << rhs.to_radians_per_second();
    }

}  // namespace quant::units::velocity
