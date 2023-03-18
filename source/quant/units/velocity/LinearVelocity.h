#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <quant/geometry/VectorQuantity.h>
#include <quant/units/position/LinearDisplacement.h>
#include <quant/units/position/Position.h>
#include <quant/units/speed.h>
#include <quant/units/time/Duration.h>


namespace quant::units::velocity
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

} // namespace quant::units::velocity


namespace quant::units::position
{

    velocity::LinearVelocity operator/(const LinearDisplacement& dx, const Duration& dt);

} // namespace quant::units::position


namespace quant
{
    using units::velocity::LinearVelocity;
} // namespace quant
