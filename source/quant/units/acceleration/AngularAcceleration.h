#pragma once

#include <quant/geometry/AngularState.h>
#include <quant/units/AxisAngle.h>
#include <quant/units/acceleration/constants.h>
#include <quant/units/acceleration/forward_declarations.h>

#include <Eigen/Geometry>

#include <ostream>

#include "quant/units/angle/constants.h"

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

        static AngularAcceleration
        radians_per_second_squared(Eigen::Quaterniond const& quaternion)
        {
            return {quaternion};
        }

        AxisAngle
        to_radians_per_second_squared() const
        {
            return {to_axis_angle(),
                    constants::names::angular_acceleration,
                    constants::symbols::radians_per_second_squared};
        }

        static AngularAcceleration
        degrees_per_second_squared(geometry::AxisAngle aa)
        {
            return {aa * angle::constants::deg2rad};
        }

        AxisAngle
        to_degrees_per_second_squared() const
        {
            return {to_axis_angle() * angle::constants::rad2deg,
                    constants::names::angular_acceleration,
                    constants::symbols::radians_per_second_squared};
        }

        std::string
        to_string() const
        {
            return to_degrees_per_second_squared().to_string();
        }

        using geometry::AngularState<AngularAcceleration>::AngularState;
    };

    inline std::ostream&
    operator<<(std::ostream& out, AngularAcceleration const& rhs)
    {
        return out << rhs.to_radians_per_second_squared();
    }

}  // namespace quant::units::acceleration
