#pragma once

#include <quant/geometry/AngularState.h>
#include <quant/units/velocity_fwd.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::velocity
{

    class AngularVelocity : public geometry::AngularState<Domain>
    {
    public:
        // Construct.

        using geometry::AngularState<Domain>::AngularState;

        static AngularVelocity
        radians_per_second(AxisAngle const& aa)
        {
            return {aa};
        }

        // Convert.

        AxisAngle
        to_radians_per_second() const
        {
            return this->to_angle_axis();
        }
    };

    std::ostream&
    operator<<(std::ostream& out, AngularVelocity const& rhs);

}  // namespace quant::units::velocity
