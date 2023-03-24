#pragma once

#include <quant/geometry/QuaternionQuantity.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::velocity
{

    class AngularVelocity : public geometry::QuaternionQuantity<AngularVelocity>
    {
    public:
        // Construct.

        using geometry::QuaternionQuantity<AngularVelocity>::QuaternionQuantity;

        static AngularVelocity
        Zero()
        {
            return Origin();
        }

        static AngularVelocity
        RadiansPerSecond(AxisAngle const& aa)
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

namespace quant
{
    using units::velocity::AngularVelocity;
}  // namespace quant
