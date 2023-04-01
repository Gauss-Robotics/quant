#pragma once

#include <quant/geometry/AngularState.h>
#include <quant/units/position_fwd.h>

#include <ostream>

namespace quant::units::position
{

    class Orientation : public geometry::AngularState<Domain>
    {
    public:
        // Construct.

        static Orientation
        radians(AxisAngle const& aa)
        {
            return {aa};
        }

        // Convert.

        AxisAngle
        to_radians() const
        {
            return this->to_angle_axis();
        }

        using geometry::AngularState<Domain>::AngularState;

        using DifferenceType = AngularDisplacement;
    };

    inline std::ostream&
    operator<<(std::ostream& out, Orientation const& rhs)
    {
        out << rhs.to_string("Orientation", "rad");
        return out;
    }

}  // namespace quant::units::position
