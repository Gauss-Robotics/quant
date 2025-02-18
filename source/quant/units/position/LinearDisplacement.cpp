#include "LinearDisplacement.h"

namespace quant::units::position
{
    LinearDisplacement
    LinearDisplacement::millimeters(geometry::Vector xyz)
    {
        return LinearDisplacement{Position::millimeters(xyz)};
    }

    LinearDisplacement
    LinearDisplacement::meters(geometry::Vector xyz)
    {
        return LinearDisplacement{Position::meters(xyz)};
    }

    Vector
    LinearDisplacement::to_millimeters() const
    {
        return {_difference_object.to_millimeters(),
                constants::names::linear_displacement,
                constants::symbols::millimeters};
    }

    Vector
    LinearDisplacement::to_meters() const
    {
        return {_difference_object.to_meters(),
                constants::names::linear_displacement,
                constants::symbols::meters};
    }

    Distance
    LinearDisplacement::to_distance() const
    {
        return Distance::millimeters(_difference_object.to_millimeters().norm());
    }

    std::ostream&
    operator<<(std::ostream& os, LinearDisplacement const& rhs)
    {
        return os << rhs.to_millimeters();
    }
}  // namespace quant::units::position