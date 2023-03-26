#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/velocity/LinearVelocity.h>
#include <quant/units/velocity_fwd.h>

namespace quant::units::velocity
{

    class LinearVelocityDifference : public LinearDifference<Domain>
    {

    public:
        using LinearDifference<Domain>::LinearDifference;
    };

}  // namespace quant::units::velocity
