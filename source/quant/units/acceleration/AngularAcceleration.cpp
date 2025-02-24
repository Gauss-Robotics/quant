#include "AngularAcceleration.h"

namespace quant::units::acceleration
{
    AngularAcceleration
    AngularAcceleration::radians_per_second_squared(geometry::AxisAngle aa)
    {
        return {aa};
    }

    AxisAngle
    AngularAcceleration::to_radians_per_second_squared() const
    {
        return {to_axis_angle(),
                constants::names::angular_acceleration,
                constants::symbols::radians_per_second_squared};
    }

    AngularAcceleration
    AngularAcceleration::degrees_per_second_squared(geometry::AxisAngle aa)
    {
        return {aa * angle::constants::deg2rad};
    }

    AxisAngle
    AngularAcceleration::to_degrees_per_second_squared() const
    {
        return {to_axis_angle() * angle::constants::rad2deg,
                constants::names::angular_acceleration,
                constants::symbols::degrees_per_second_squared};
    }

    std::string
    AngularAcceleration::to_string() const
    {
        return to_degrees_per_second_squared().to_string();
    }

    std::ostream&
    operator<<(std::ostream& out, AngularAcceleration const& rhs)
    {
        return out << rhs.to_radians_per_second_squared();
    }
}  // namespace quant::units::acceleration