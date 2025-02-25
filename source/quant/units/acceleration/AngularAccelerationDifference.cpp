#include "AngularAccelerationDifference.h"

namespace quant::units::acceleration
{

    AngularAccelerationDifference
    AngularAccelerationDifference::radians_per_second_squared(geometry::AxisAngle aa)
    {
        return AngularAccelerationDifference{AngularAcceleration::radians_per_second_squared(aa)};
    }

    AxisAngle
    AngularAccelerationDifference::to_radians_per_second_squared() const
    {
        return _difference_object.to_radians_per_second_squared();
    }

    AngularAccelerationDifference
    AngularAccelerationDifference::degrees_per_second_squared(geometry::AxisAngle aa)
    {
        return AngularAccelerationDifference{AngularAcceleration::degrees_per_second_squared(aa)};
    }

    AxisAngle
    AngularAccelerationDifference::to_degrees_per_second_squared() const
    {
        return _difference_object.to_degrees_per_second_squared();
    }

    std::ostream&
    operator<<(std::ostream& out, AngularAccelerationDifference const& rhs)
    {
        return out << rhs.to_radians_per_second_squared();
    }
}  // namespace quant::units::acceleration