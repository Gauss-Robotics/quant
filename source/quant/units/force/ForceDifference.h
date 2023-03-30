#pragma once

#include <quant/geometry/LinearDifference.h>
#include <quant/units/force/Force.h>
#include <quant/units/force_fwd.h>

namespace quant::units::force
{

    class ForceDifference : public geometry::LinearDifference<Domain>
    {

    public:
        using LinearDifference<Domain>::LinearDifference;

        using StateType = Force;
    };

}  // namespace quant::units::force
