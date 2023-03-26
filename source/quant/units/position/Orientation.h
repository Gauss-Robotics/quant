#pragma once

#include <quant/geometry/QuaternionQuantity.h>
#include <quant/units/position_fwd.h>

#include <ostream>

namespace quant::units::position
{

    class Orientation : public geometry::QuaternionQuantity<Domain>
    {
    public:
        // Construct.

        using geometry::QuaternionQuantity<Domain>::QuaternionQuantity;

        static Orientation
        Radians(AxisAngle const& aa)
        {
            return {aa};
        }

        // Convert.

        AxisAngle
        toRadians() const
        {
            return this->toAngleAxis();
        }
    };

    inline std::ostream&
    operator<<(std::ostream& out, Orientation const& rhs)
    {
        out << rhs.toString("Orientation", "rad");
        return out;
    }

}  // namespace quant::units::position
