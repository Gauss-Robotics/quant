#pragma once

#include <quant/geometry/AngularState.h>
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
        newton_meters(AxisAngle aa)
        {
            return {aa};
        }
    };

    std::ostream&
    operator<<(std::ostream& out, Torque const& rhs);

}  // namespace quant::units::force
