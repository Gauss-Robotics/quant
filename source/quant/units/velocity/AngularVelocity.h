#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <simox/core/geometry/QuaternionQuantity.h>


namespace simox::core::units::velocity
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

} // namespace simox::core::units::velocity


namespace simox
{
    using core::units::velocity::AngularVelocity;
} // namespace simox
