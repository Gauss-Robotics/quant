#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <simox/core/geometry/VectorQuantity.h>
#include <simox/core/geometry/common.h> // for Delta
#include <simox/core/units/position/Displacement.h>
#include <simox/core/units/position/Position.h>
#include <simox/core/units/speed.h>
#include <simox/core/units/time/Duration.h>


namespace simox::core::units::velocity
{

    class LinearVelocity : public geometry::VectorQuantity<LinearVelocity>
    {
        // Construct.
    public:
        using geometry::VectorQuantity<LinearVelocity>::VectorQuantity;

        static LinearVelocity
        Zero()
        {
            return Origin();
        }

        static LinearVelocity
        MilliMetersPerSecond(Vector xyz)
        {
            return {xyz.x, xyz.y, xyz.z};
        }

        static LinearVelocity
        MetersPerSecond(Vector xyz)
        {
            constexpr int m2mm = 1'000;
            return {xyz.x * m2mm, xyz.y * m2mm, xyz.z * m2mm};
        }

        Speed
        toSpeed() const
        {
            return Speed::MilliMetersPerSecond(toMagnitude().toScalar());
        }
    };


    std::ostream& operator<<(std::ostream& out, const LinearVelocity& rhs);

} // namespace simox::core::units::velocity


namespace simox::core::units::position
{

    velocity::LinearVelocity operator/(const Displacement& dx, const Duration& dt);

} // namespace simox::core::units::position


namespace simox
{
    using core::units::velocity::LinearVelocity;
} // namespace simox
