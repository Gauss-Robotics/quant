#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/velocity/LinearVelocity.h>
#include <quant/units/velocity/forward_declarations.h>

namespace quant::units::velocity
{

    class LinearVelocityDifference : public geometry::Difference<LinearVelocity>
    {

    public:
        using geometry::Difference<LinearVelocity>::Difference;
    };

}  // namespace quant::units::velocity
