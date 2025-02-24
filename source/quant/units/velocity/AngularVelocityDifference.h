#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/Difference.h>
#include <quant/units/velocity/AngularVelocity.h>
#include <quant/units/velocity/forward_declarations.h>

namespace quant::units::velocity
{

    class AngularVelocityDifference : public geometry::Difference<AngularVelocity>
    {

    public:
        static AngularVelocityDifference
        radians_per_second(geometry::AxisAngle const& aa);

        static AngularVelocityDifference
        degrees_per_second(geometry::AxisAngle const& aa);

        AxisAngle
        to_radians_per_second() const;

        AxisAngle
        to_degrees_per_second() const;

        std::string to_string() const;

        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& os, AngularVelocityDifference const& rhs);

}  // namespace quant::units::velocity
