#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/acceleration/AngularAcceleration.h>
#include <quant/units/acceleration/forward_declarations.h>

namespace quant::units::acceleration
{
    class AngularAccelerationDifference : public geometry::Difference<AngularAcceleration>
    {
    public:
        static AngularAccelerationDifference
        radians_per_second_squared(geometry::AxisAngle aa)
        {
            return AngularAccelerationDifference{
                AngularAcceleration::radians_per_second_squared(aa)};
        }

        static AngularAccelerationDifference
        radians_per_second_squared(Eigen::Quaterniond const& quaternion)
        {
            return AngularAccelerationDifference{
                AngularAcceleration::radians_per_second_squared(quaternion)};
        }

        AxisAngle
        to_radians_per_second_squared() const
        {
            return _difference_object.to_radians_per_second_squared();
        }

        static AngularAccelerationDifference
        degrees_per_second_squared(geometry::AxisAngle aa)
        {
            return AngularAccelerationDifference{
                AngularAcceleration::degrees_per_second_squared(aa)};
        }

        AxisAngle
        to_degrees_per_second_squared() const
        {
            return _difference_object.to_degrees_per_second_squared();
        }

        using geometry::Difference<AngularAcceleration>::Difference;
    };

    inline std::ostream&
    operator<<(std::ostream& out, AngularAccelerationDifference const& rhs)
    {
        return out << rhs.to_radians_per_second_squared();
    }
}  // namespace quant::units::acceleration