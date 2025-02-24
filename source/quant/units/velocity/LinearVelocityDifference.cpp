#include "LinearVelocityDifference.h"

namespace quant::units::velocity
{
    LinearVelocityDifference
    LinearVelocityDifference::millimeters_per_second(geometry::Vector xyz)
    {
        return LinearVelocityDifference{LinearVelocity::millimeters_per_second(xyz)};
    }

    LinearVelocityDifference
    LinearVelocityDifference::meters_per_second(geometry::Vector xyz)
    {
        return LinearVelocityDifference{LinearVelocity::meters_per_second(xyz)};
    }

    Vector
    LinearVelocityDifference::to_millimeters_per_second() const
    {
        return _difference_object.to_millimeters_per_second();
    }

    Vector
    LinearVelocityDifference::to_meters_per_second() const
    {
        return _difference_object.to_meters_per_second();
    }

    SpeedDifference
    LinearVelocityDifference::to_speed_difference() const
    {
        return SpeedDifference::millimeters_per_second(to_millimeters_per_second().norm());
    }

    std::string
    LinearVelocityDifference::to_string() const
    {
        return _difference_object.to_string();
    }

    std::ostream&
    operator<<(std::ostream& os, LinearVelocityDifference const& rhs)
    {
        return os << rhs.to_string();
    }
}  // namespace quant::units::velocity