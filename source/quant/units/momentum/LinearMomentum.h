#pragma once

#include <quant/geometry/T3TangentState.h>
#include <quant/units/Vector.h>
#include <quant/units/mass/Mass.h>
#include <quant/units/momentum/constants.h>
#include <quant/units/momentum/forward_declarations.h>
#include <quant/units/velocity/LinearVelocity.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::momentum
{

    class LinearMomentum : public geometry::T3TangentState<LinearMomentum>
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

        std::string
        to_string() const
        {
            return to_kilogram_meters_per_second().to_string();
        }

        using T3TangentState::T3TangentState;
    };

    inline std::ostream&
    operator<<(std::ostream& os, LinearMomentum const& rhs)
    {
        return os << rhs.to_string();
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
