#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/Vector.h>
#include <quant/units/acceleration/LinearAcceleration.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::acceleration
{

    class LinearAccelerationDifference : public geometry::Difference<LinearAcceleration>
    {
    public:
        static LinearAccelerationDifference
        millimeters_per_second_squared(geometry::Vector const& xyz);

        static LinearAccelerationDifference
        meters_per_second_squared(geometry::Vector const& xyz);

        Vector
        to_millimeters_per_second_squared() const;

        Vector
        to_meters_per_second_squared() const;

        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& os, LinearAccelerationDifference const& rhs);

}  // namespace quant::units::acceleration
