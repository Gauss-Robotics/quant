#pragma once

#include <quant/geometry/AngularState.h>
#include <quant/units/AxisAngle.h>
#include <quant/units/acceleration/constants.h>
#include <quant/units/acceleration/forward_declarations.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::acceleration
{

    class AngularAcceleration : public geometry::AngularState<AngularAcceleration>
    {
    public:
        static AngularAcceleration
        radians_per_second_squared(geometry::AxisAngle aa)
        {
            return {aa};
        }

        AxisAngle
        to_radians_per_second_squared() const
        {
            return {to_axis_angle(),
                    constants::names::angular_acceleration,
                    constants::symbols::radians_per_second_squared};
        }

        using geometry::AngularState<AngularAcceleration>::AngularState;
    };

    inline std::ostream&
    operator<<(std::ostream& out, AngularAcceleration const& rhs)
    {
        return out << rhs.to_radians_per_second_squared();
    }

}  // namespace quant::units::acceleration
