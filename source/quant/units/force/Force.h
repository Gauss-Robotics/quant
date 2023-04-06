#pragma once

#include <quant/geometry/LinearState.h>
#include <quant/units/Vector.h>
#include <quant/units/acceleration/LinearAcceleration.h>
#include <quant/units/force/constants.h>
#include <quant/units/force_fwd.h>
#include <quant/units/mass/Mass.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::force
{

    class Force : public geometry::LinearState<Domain>
    {
    public:
        static Force
        newton(geometry::Vector xyz)
        {
            return {xyz};
        }

        Vector
        to_newton() const
        {
            return {to_vector(), constants::names::force, constants::symbols::newton};
        }

        using geometry::LinearState<Domain>::LinearState;
    };

    inline std::ostream&
    operator<<(std::ostream& os, Force const& rhs)
    {
        return os << rhs.to_newton();
    }

}  // namespace quant::units::force

namespace quant
{

    inline Force
    operator*(Mass const& lhs, LinearAcceleration const& rhs)
    {
        return Force::newton(rhs.to_meters_per_second_squared() * lhs.to_kilograms());
    }

}  // namespace quant
