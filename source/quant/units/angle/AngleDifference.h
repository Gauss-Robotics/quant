#pragma once

#include <quant/geometry/Scalar.h>
#include <quant/geometry/ScalarState.h>
#include <quant/units/angle/forward_declarations.h>

namespace quant::units::angle
{

    class Angle : public geometry::ScalarState<Angle>
    {
    public:
        static Angle
        radians(geometry::Scalar radians)
        {
            return {radians};
        }

    protected:
        using geometry::ScalarState<Angle>::ScalarState;
    };

}  // namespace quant::units::angle
