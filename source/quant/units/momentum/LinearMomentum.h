#pragma once

#include <quant/geometry/LinearState.h>
#include <quant/units/Vector.h>
#include <quant/units/mass/Mass.h>
#include <quant/units/momentum/constants.h>
#include <quant/units/momentum_fwd.h>
#include <quant/units/velocity/LinearVelocity.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::momentum
{

    class LinearMomentum : public geometry::LinearState<Domain>
    {
    public:
        static LinearMomentum
        kilogram_meters_per_second(geometry::Vector xyz)
        {
            return {xyz};
        }

        Vector
        to_kilogram_meters_per_second() const
        {
            return {to_vector(),
                    constants::names::linear_momentum,
                    constants::symbols::kilogram_meters_per_second};
        }

        using geometry::LinearState<Domain>::LinearState;
    };

    inline std::ostream&
    operator<<(std::ostream& os, LinearMomentum const& rhs)
    {
        return os << rhs.to_kilogram_meters_per_second();
    }

}  // namespace quant::units::momentum

namespace quant
{

    inline LinearMomentum
    operator*(Mass const& lhs, LinearVelocity const& rhs)
    {
        return LinearMomentum::kilogram_meters_per_second(rhs.to_meters_per_second() *
                                                          lhs.to_kilograms());
    }

}  // namespace quant
