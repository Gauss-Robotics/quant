#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/Vector.h>
#include <quant/units/length/Distance.h>
#include <quant/units/position/Position.h>
#include <quant/units/position/constants.h>
#include <quant/units/position/forward_declarations.h>

namespace quant::units::position
{

    class LinearDisplacement : public geometry::Difference<Position>
    {

    public:
        static LinearDisplacement
        millimeters(geometry::Vector xyz);

        static LinearDisplacement
        meters(geometry::Vector xyz);

        Vector
        to_millimeters() const;

        Distance
        to_distance() const;

        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& os, LinearDisplacement const& rhs);

}  // namespace quant::units::position
