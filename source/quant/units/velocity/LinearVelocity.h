#pragma once

#include <quant/geometry/LinearState.h>
#include <quant/units/position/LinearDisplacement.h>
#include <quant/units/position/Position.h>
#include <quant/units/speed/Speed.h>
#include <quant/units/time/Duration.h>
#include <quant/units/velocity_fwd.h>

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
    class LinearVelocity : public geometry::LinearState<Domain>
    {
        // Construct.
    public:
        static LinearVelocity
        milli_meters_per_second(Vector xyz)
        {
            return {xyz.x, xyz.y, xyz.z};
        }

        static LinearVelocity
        meters_per_second(Vector xyz)
        {
            constexpr int m2mm = 1'000;
            return {xyz.x * m2mm, xyz.y * m2mm, xyz.z * m2mm};
        }

        Speed
        to_speed() const
        {
            return Speed::milli_meters_per_second(representation_.norm());
        }

        using geometry::LinearState<Domain>::LinearState;
    };

    std::ostream&
    operator<<(std::ostream& out, LinearVelocity const& rhs);

}  // namespace quant::units::velocity

namespace quant::units::position
{

    velocity::LinearVelocity
    operator/(LinearDisplacement const& dx, Duration const& dt);

}  // namespace quant::units::position
