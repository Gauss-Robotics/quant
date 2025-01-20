#pragma once

#include <quant/geometry/AngularState.h>
#include <quant/units/AxisAngle.h>
#include <quant/units/position/constants.h>
#include <quant/units/angle/constants.h>
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
        static Orientation
        radians(Eigen::Quaterniond const& q)
        {
            return {q};
        }
        static Orientation
        degrees(geometry::AxisAngle const& aa)
        {
            return radians(aa * angle::constants::deg2rad);
        }
        static Orientation
        degrees(Eigen::Quaterniond const& q)
        {
            return radians(q);
        }

        AxisAngle
        to_radians() const
        {
            return {to_axis_angle(), constants::names::orientation, constants::symbols::radians};
        }

        AxisAngle
        to_degrees() const
        {
            return {to_axis_angle() * angle::constants::rad2deg,
                    constants::names::orientation,
                    constants::symbols::degrees};
        }

        std::string
        to_string() const
        {
            return to_degrees().to_string();
        }

        using geometry::AngularState<Orientation>::AngularState;
    };

    inline std::ostream&
    operator<<(std::ostream& out, Orientation const& rhs)
    {
        return out << rhs.to_radians();
    }

}  // namespace quant::units::position
