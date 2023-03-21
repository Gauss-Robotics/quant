#pragma once

#include <quant/geometry/VectorQuantity.h>
#include <quant/units/position/LinearDisplacement.h>
#include <quant/units/position/Position.h>
#include <quant/units/speed/Speed.h>
#include <quant/units/time/Duration.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::velocity
{

    /**
     * @brief An object of this class describes a linear velocity.
     *
     * - The difference of a LinearVelocity is LinearVelocityDifference.
     * - The magnitude of a Linear Veloctiy is Speed.
     */
    class LinearVelocity :
        public geometry::VectorQuantity<LinearVelocity, Difference<LinearVelocity>>
    {
        // Construct.
    public:
        using geometry::VectorQuantity<LinearVelocity, Difference<LinearVelocity>>::VectorQuantity;

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
            return Speed::MilliMetersPerSecond(representation_.norm());
        }
    };

    std::ostream& operator<<(std::ostream& out, LinearVelocity const& rhs);

}  // namespace quant::units::velocity

namespace quant::units::position
{

    velocity::LinearVelocity operator/(LinearDisplacement const& dx, Duration const& dt);

}  // namespace quant::units::position

namespace quant
{

    using units::velocity::LinearVelocity;

}  // namespace quant
