#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/force/Force.h>
#include <quant/units/force_fwd.h>

namespace quant::units::force
{

    class ForceDifference : public LinearDifference<Domain>
    {

    public:
        using LinearDifference<Domain>::LinearDifference;
    };

}  // namespace quant::units::force
