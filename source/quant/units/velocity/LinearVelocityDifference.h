#pragma once

#include <quant/geometry/LinearDifference.h>
#include <quant/units/velocity/LinearVelocity.h>
#include <quant/units/velocity_fwd.h>

namespace quant::units::velocity
{

    class LinearVelocityDifference : public geometry::LinearDifference<Domain>
    {

    public:
        using LinearDifference<Domain>::LinearDifference;

        using StateType = LinearVelocity;
    };

}  // namespace quant::units::velocity
