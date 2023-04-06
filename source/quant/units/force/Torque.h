#pragma once

#include <quant/geometry/AngularState.h>
#include <quant/units/AxisAngle.h>
#include <quant/units/force/constants.h>
#include <quant/units/force_fwd.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::force
{

    class Torque : public geometry::AngularState<Domain>
    {
        // Construct.
    public:
        using geometry::AngularState<Domain>::AngularState;

        static Torque
        newton_meters(geometry::AxisAngle aa)
        {
            return {aa};
        }

        AxisAngle
        to_newton_meters() const
        {
            return {to_axis_angle(), constants::names::torque, constants::symbols::newton_meters};
        }
    };

    inline std::ostream&
    operator<<(std::ostream& out, Torque const& rhs)
    {
        return out << rhs.to_newton_meters();
    }

}  // namespace quant::units::force
