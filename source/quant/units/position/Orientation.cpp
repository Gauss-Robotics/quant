#include "Orientation.h"

namespace quant::units::position
{
    Orientation
    Orientation::radians(geometry::AxisAngle const& aa)
    {
        return {aa};
    }

    Orientation
    Orientation::radians(Eigen::Quaterniond const& q)
    {
        return {q};
    }

    Orientation
    Orientation::degrees(geometry::AxisAngle const& aa)
    {
        return radians(aa * angle::constants::deg2rad);
    }

    Orientation
    Orientation::degrees(Eigen::Quaterniond const& q)
    {
        return radians(q);
    }

    AxisAngle
    Orientation::to_radians() const
    {
        return {to_axis_angle(), constants::names::orientation, constants::symbols::radians};
    }

    AxisAngle
    Orientation::to_degrees() const
    {
        return {to_axis_angle() * angle::constants::rad2deg,
                constants::names::orientation,
                constants::symbols::degrees};
    }

    std::string
    Orientation::to_string() const
    {
        return to_degrees().to_string();
    }

    std::ostream&
    operator<<(std::ostream& out, Orientation const& rhs)
    {
        return out << rhs.to_degrees();
    }
}  // namespace quant::units::position