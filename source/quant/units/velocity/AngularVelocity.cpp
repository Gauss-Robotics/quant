#include "AngularVelocity.h"

namespace quant::units::velocity
{
    AngularVelocity
    AngularVelocity::radians_per_second(geometry::AxisAngle const& aa)
    {
        return {aa};
    }

    AngularVelocity
    AngularVelocity::radians_per_second(geometry::Vector const& vector)
    {
        const auto norm = vector.norm();
        return radians_per_second({.axis = vector / norm, .angle = norm});
    }

    AngularVelocity
    AngularVelocity::degrees_per_second(geometry::AxisAngle const& aa)
    {
        return {aa * angle::constants::deg2rad};
    }

    AngularVelocity
    AngularVelocity::degrees_per_second(geometry::Vector const& vector)
    {
        const auto norm = vector.norm();
        return degrees_per_second({.axis = vector / norm, .angle = norm});
    }

    AxisAngle
    AngularVelocity::to_radians_per_second() const
    {
        return {to_axis_angle(),
                constants::names::angular_velocity,
                constants::symbols::radians_per_second};
    }

    AxisAngle
    AngularVelocity::to_degrees_per_second() const
    {
        return {to_axis_angle() * angle::constants::rad2deg,
                constants::names::angular_velocity,
                constants::symbols::radians_per_second};
    }

    AngularSpeed
    AngularVelocity::to_angular_speed() const
    {
        return AngularSpeed::radians_per_second(to_radians_per_second().angle);
    }

    std::string
    AngularVelocity::to_string() const
    {
        return to_degrees_per_second().to_string();
    }

    std::ostream&
    operator<<(std::ostream& out, AngularVelocity const& rhs)
    {
        return out << rhs.to_radians_per_second();
    }
}  // namespace quant::units::velocity