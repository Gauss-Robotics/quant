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
        toRadians() const
        {
            return this->toAngleAxis();
        }

        using geometry::AngularState<Domain>::AngularState;

        using DifferenceType = AngularDisplacement;
    };

    inline std::ostream&
    operator<<(std::ostream& out, Orientation const& rhs)
    {
        out << rhs.toString("Orientation", "rad");
        return out;
    }

}  // namespace quant::units::position
