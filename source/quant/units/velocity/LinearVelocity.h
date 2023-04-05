#pragma once

#include <quant/geometry/LinearState.h>
#include <quant/units/position/LinearDisplacement.h>
#include <quant/units/position/Position.h>
#include <quant/units/speed/Speed.h>
#include <quant/units/time/Duration.h>
#include <quant/units/velocity_constants.h>
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
    public:
        static LinearVelocity
        millimeters_per_second(geometry::Vector xyz)
        {
            return {xyz};
        }

        static LinearVelocity
        meters_per_second(geometry::Vector xyz)
        {
            return {xyz * constants::mps2mmps};
        }

        Vector
        to_millimeters_per_second() const
        {
            return {
                to_vector(), constants::linear_velocity_name, constants::millimeters_per_second};
        }

        Vector
        to_meters_per_second() const
        {
            return {to_vector() * constants::mmps2mps,
                    constants::linear_velocity_name,
                    constants::meters_per_second};
        }

        Speed
        to_speed() const
        {
            return Speed::milli_meters_per_second(representation_.norm());
        }

        using geometry::LinearState<Domain>::LinearState;
    };

    inline std::ostream&
    operator<<(std::ostream& os, LinearVelocity const& rhs)
    {
        return os << rhs.to_millimeters_per_second();
    }

}  // namespace quant::units::velocity

namespace quant::units::position
{

    velocity::LinearVelocity
    operator/(LinearDisplacement const& dx, Duration const& dt);

}  // namespace quant::units::position
