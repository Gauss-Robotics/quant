#include "LinearAccelerationDifference.h"

#include <quant/units/acceleration/LinearAcceleration.h>

namespace quant::units::acceleration
{

    LinearAccelerationDifference
    LinearAccelerationDifference::millimeters_per_second_squared(geometry::Vector const& xyz)
    {
        return LinearAccelerationDifference{
            LinearAcceleration::millimeters_per_second_squared(xyz)};
    }

    LinearAccelerationDifference
    LinearAccelerationDifference::millimeters_per_second_squared(Eigen::Vector3d const& xyz)
    {
        return LinearAccelerationDifference{
            LinearAcceleration::millimeters_per_second_squared(xyz)};
    }

    LinearAccelerationDifference
    LinearAccelerationDifference::meters_per_second_squared(geometry::Vector const& xyz)
    {
        return LinearAccelerationDifference{LinearAcceleration::meters_per_second_squared(xyz)};
    }

    LinearAccelerationDifference
    LinearAccelerationDifference::meters_per_second_squared(Eigen::Vector3d const& xyz)
    {
        return LinearAccelerationDifference{LinearAcceleration::meters_per_second_squared(xyz)};
    }

    Vector
    LinearAccelerationDifference::to_millimeters_per_second_squared() const
    {
        return _difference_object.to_millimeters_per_second_squared();
    }

    Vector
    LinearAccelerationDifference::to_meters_per_second_squared() const
    {
        return _difference_object.to_meters_per_second_squared();
    }

    std::ostream&
    operator<<(std::ostream& os, LinearAccelerationDifference const& rhs)
    {
        return os << rhs.to_millimeters_per_second_squared();
    }
}  // namespace quant::units::acceleration