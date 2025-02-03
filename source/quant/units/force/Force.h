#pragma once

#include <quant/geometry/LinearState.h>
#include <quant/units/Vector.h>
#include <quant/units/acceleration/LinearAcceleration.h>
#include <quant/units/force/constants.h>
#include <quant/units/force/forward_declarations.h>
#include <quant/units/mass/Mass.h>
#include <quant/units/momentum/LinearImpulse.h>
#include <quant/units/time/Duration.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::force
{

    class Force : public geometry::LinearState<Force>
    {
    public:
        static Force
        newton(geometry::Vector xyz);

        Vector
        to_newton() const;

        std::string
        to_string() const;

        using LinearState::LinearState;
    };

    std::ostream&
    operator<<(std::ostream& os, Force const& rhs);

}  // namespace quant::units::force

namespace quant
{

    inline Force
    operator*(Mass const& lhs, LinearAcceleration const& rhs)
    {
        return Force::newton(rhs.to_meters_per_second_squared() * lhs.to_kilograms());
    }

    inline Force
    operator/(LinearImpulse const& lhs, Duration const& rhs)
    {
        return Force::newton(lhs.to_newton_seconds() / rhs.to_seconds());
    }

}  // namespace quant
