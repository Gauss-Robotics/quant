#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/Difference.h>
#include <quant/units/position/Orientation.h>
#include <quant/units/position/Position.h>
#include <quant/units/position/forward_declarations.h>

namespace quant::units::position
{

    class AngularDisplacement : public geometry::Difference<Orientation>
    {
    public:
        static AngularDisplacement
        radians(geometry::AxisAngle const& aa);

        static AngularDisplacement
        degrees(geometry::AxisAngle const& aa);

        static AngularDisplacement
        radians(Eigen::Quaterniond const& q);

        static AngularDisplacement
        degrees(Eigen::Quaterniond const& q);

        AxisAngle
        to_radians() const;

        AxisAngle
        to_degrees() const;

        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& os, AngularDisplacement const& rhs);

}  // namespace quant::units::position
