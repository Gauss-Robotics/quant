#pragma once

#include <quant/geometry/AngularState.h>
#include <quant/units/AxisAngle.h>
#include <quant/units/position/constants.h>
#include <quant/units/position/forward_declarations.h>

#include <ostream>

namespace quant::units::position
{

    class Orientation : public geometry::AngularState<Orientation>
    {
    public:
        static Orientation
        radians(geometry::AxisAngle const& aa)
        {
            return {aa};
        }

        AxisAngle
        to_radians() const
        {
            return {to_axis_angle(), constants::names::orientation, constants::symbols::radians};
        }

        std::string
        to_string() const
        {
            return to_radians().to_string();
        }

        using geometry::AngularState<Orientation>::AngularState;
    };

    inline std::ostream&
    operator<<(std::ostream& out, Orientation const& rhs)
    {
        return out << rhs.to_radians();
    }

}  // namespace quant::units::position
