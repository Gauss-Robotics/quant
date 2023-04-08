#pragma once

#include <quant/geometry/LinearState.h>
#include <quant/units/Vector.h>
#include <quant/units/position_fwd.h>
#include <quant/units/speed/Speed.h>
#include <quant/units/time/Duration.h>
#include <quant/units/velocity/constants.h>
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
            return {to_vector(),
                    constants::names::linear_velocity,
                    constants::symbols::millimeters_per_second};
        }

        Vector
        to_meters_per_second() const
        {
            return {to_vector() * constants::mmps2mps,
                    constants::names::linear_velocity,
                    constants::symbols::meters_per_second};
        }

        Speed
        to_speed() const
        {
            return Speed::millimeters_per_second(_representation.norm());
        }

        std::string
        to_string() const
        {
            Vector (LinearVelocity::*member_function_ptr)();

            for (auto fn : {&LinearVelocity::to_meters_per_second})
            {
                Vector v = (this->*fn)();
                if (v.x > 1 or v.y > 1 or v.z > 1)
                {
                    return v.to_string();
                }
            }

            return to_millimeters_per_second().to_string();
        }

        using geometry::LinearState<Domain>::LinearState;
    };

    inline std::ostream&
    operator<<(std::ostream& os, LinearVelocity const& rhs)
    {
        return os << rhs.to_string();
    }

}  // namespace quant::units::velocity

namespace quant
{

    LinearVelocity
    operator/(LinearDisplacement const& dx, Duration const& dt);

}  // namespace quant
