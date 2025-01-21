#pragma once

#include <quant/geometry/LinearState.h>
#include <quant/units/Vector.h>
#include <quant/units/acceleration/constants.h>
#include <quant/units/acceleration/forward_declarations.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::acceleration
{

    class LinearAccelerationDifference : public geometry::Difference<LinearAcceleration>
    {
    public:
        static LinearAccelerationDifference
        millimeters_per_second_squared(const geometry::Vector& xyz)
        {
            return LinearAccelerationDifference{LinearAcceleration::millimeters_per_second_squared(xyz)};
        }

        static LinearAccelerationDifference
        millimeters_per_second_squared(const Eigen::Vector3d& xyz)
        {
            return LinearAccelerationDifference{LinearAcceleration::millimeters_per_second_squared(xyz)};
        }

        static LinearAccelerationDifference
        meters_per_second_squared(const geometry::Vector& xyz)
        {
            return LinearAccelerationDifference{LinearAcceleration::meters_per_second_squared(xyz)};
        }

        static LinearAccelerationDifference
        meters_per_second_squared(const Eigen::Vector3d& xyz)
        {
            return LinearAccelerationDifference{LinearAcceleration::meters_per_second_squared(xyz)};
        }

        Vector
        to_millimeters_per_second_squared() const
        {
            return _difference_object.to_millimeters_per_second_squared();
        }

        Vector
        to_meters_per_second_squared() const
        {
            return _difference_object.to_meters_per_second_squared();
        }

        using geometry::Difference<LinearAcceleration>::Difference;
    };

    inline std::ostream&
    operator<<(std::ostream& os, LinearAccelerationDifference const& rhs)
    {
        return os << rhs.to_millimeters_per_second_squared();
    }

}  // namespace quant::units::acceleration
