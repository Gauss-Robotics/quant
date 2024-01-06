#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/momentum/LinearMomentum.h>
#include <quant/units/momentum/forward_declarations.h>

namespace quant::units::momentum
{

    class LinearImpulse : public geometry::Difference<LinearMomentum>
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

        using geometry::Difference<LinearMomentum>::Difference;
    };

}  // namespace quant::units::momentum
