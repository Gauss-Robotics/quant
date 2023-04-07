#pragma once

#include <quant/geometry/LinearDifference.h>
#include <quant/units/momentum/LinearMomentum.h>
#include <quant/units/momentum_fwd.h>

namespace quant::units::momentum
{

    class LinearImpulse : public geometry::LinearDifference<Domain>
    {

    public:
        static LinearImpulse
        newton_seconds(geometry::Vector newton_seconds)
        {
            return LinearImpulse{LinearMomentum::kilogram_meters_per_second(newton_seconds)};
        }

        Vector
        to_newton_seconds() const
        {
            return {_difference_object.to_kilogram_meters_per_second(),
                    constants::names::linear_impulse,
                    constants::symbols::newton_seconds};
        }

        using LinearDifference<Domain>::LinearDifference;
    };

}  // namespace quant::units::momentum
