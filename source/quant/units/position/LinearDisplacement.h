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
        millimeters(geometry::Vector xyz)
        {
            return LinearDisplacement{Position::millimeters(xyz)};
        }

        static LinearDisplacement
        meters(geometry::Vector xyz)
        {
            return LinearDisplacement{Position::meters(xyz)};
        }

        Vector
        to_millimeters() const
        {
            return {_difference_object.to_millimeters(),
                    constants::names::linear_displacement,
                    constants::symbols::millimeters};
        }

        Distance
        to_distance() const
        {
            return Distance::millimeters(_difference_object.to_millimeters().norm());
        }

        using geometry::Difference<Position>::Difference;
    };

    inline std::ostream&
    operator<<(std::ostream& os, LinearDisplacement const& rhs)
    {
        return os << rhs.to_millimeters();
    }

}  // namespace quant::units::position
