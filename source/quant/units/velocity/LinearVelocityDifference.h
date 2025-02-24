#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/speed/SpeedDifference.h>
#include <quant/units/velocity/LinearVelocity.h>
#include <quant/units/velocity/forward_declarations.h>

namespace quant::units::velocity
{

    class LinearVelocityDifference : public geometry::Difference<LinearVelocity>
    {
    public:
        static LinearVelocityDifference
        millimeters_per_second(geometry::Vector xyz);

        static LinearVelocityDifference
        meters_per_second(geometry::Vector xyz);

        Vector
        to_millimeters_per_second() const;

        Vector
        to_meters_per_second() const;

        SpeedDifference
        to_speed_difference() const;

        std::string
        to_string() const;

        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& os, LinearVelocityDifference const& rhs);

}  // namespace quant::units::velocity
