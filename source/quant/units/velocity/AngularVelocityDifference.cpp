#include "AngularVelocityDifference.h"

namespace quant::units::velocity
{
    AngularVelocityDifference
    AngularVelocityDifference::radians_per_second(geometry::AxisAngle const& aa)
    {
        return AngularVelocityDifference{AngularVelocity::radians_per_second(aa)};
    }

    AngularVelocityDifference
    AngularVelocityDifference::degrees_per_second(geometry::AxisAngle const& aa)
    {
        return AngularVelocityDifference{AngularVelocity::degrees_per_second(aa)};
    }

    AxisAngle
    AngularVelocityDifference::to_radians_per_second() const
    {
        return _difference_object.to_radians_per_second();
    }

    AxisAngle
    AngularVelocityDifference::to_degrees_per_second() const
    {
        return _difference_object.to_degrees_per_second();
    }

    std::string
    AngularVelocityDifference::to_string() const
    {
        return to_degrees_per_second().to_string();
    }

    std::ostream&
    operator<<(std::ostream& os, AngularVelocityDifference const& rhs)
    {
        return os << rhs.to_string();
    }
}  // namespace quant::units::velocity