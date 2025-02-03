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
        radians_per_second_squared(geometry::AxisAngle aa);

        static AngularAccelerationDifference
        radians_per_second_squared(Eigen::Quaterniond const& quaternion);

        AxisAngle
        to_radians_per_second_squared() const;

        static AngularAccelerationDifference
        degrees_per_second_squared(geometry::AxisAngle aa);

        AxisAngle
        to_degrees_per_second_squared() const;

        using geometry::Difference<AngularAcceleration>::Difference;
    };

    std::ostream&
    operator<<(std::ostream& out, AngularAccelerationDifference const& rhs);
}  // namespace quant::units::acceleration