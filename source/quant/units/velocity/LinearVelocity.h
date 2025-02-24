#pragma once

#include <quant/geometry/T3TangentState.h>
#include <quant/units/Vector.h>
#include <quant/units/position/forward_declarations.h>
#include <quant/units/speed/Speed.h>
#include <quant/units/time/Duration.h>
#include <quant/units/velocity/constants.h>
#include <quant/units/velocity/forward_declarations.h>

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
    class LinearVelocity : public geometry::T3TangentState<LinearVelocity>
    {
    public:
        static LinearVelocity
        millimeters_per_second(geometry::Vector xyz);

        static LinearVelocity
        meters_per_second(geometry::Vector xyz);

        Vector
        to_millimeters_per_second() const;

        Vector
        to_meters_per_second() const;

        Speed
        to_speed() const;

        std::string
        to_string() const;

        using T3TangentState::T3TangentState;
    };

    std::ostream&
    operator<<(std::ostream& os, LinearVelocity const& rhs);

}  // namespace quant::units::velocity

namespace quant
{

    LinearVelocity
    operator/(LinearDisplacement const& dx, Duration const& dt);

}  // namespace quant
