#pragma once

#include <quant/geometry/QuaternionQuantity.h>
#include <quant/units/velocity_fwd.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::velocity
{

    class AngularVelocity : public geometry::QuaternionQuantity<Domain>
    {
    public:
        // Construct.

        using geometry::QuaternionQuantity<Domain>::QuaternionQuantity;

        static AngularVelocity
        radiansPerSecond(AxisAngle const& aa)
        {
            return {aa};
        }

        // Convert.

        AxisAngle
        toRadiansPerSecond() const
        {
            return this->toAngleAxis();
        }
    };

    std::ostream&
    operator<<(std::ostream& out, AngularVelocity const& rhs);

}  // namespace quant::units::velocity
