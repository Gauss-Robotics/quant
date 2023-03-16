#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <quant/geometry/QuaternionQuantity.h>


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
        RadiansPerSecond(const AxisAngle& aa)
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


    std::ostream& operator<<(std::ostream& out, const AngularVelocity& rhs);

} // namespace quant::units::velocity


namespace quant
{
    using units::velocity::AngularVelocity;
} // namespace quant
