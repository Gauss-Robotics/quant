#pragma once

#include <quant/framed_geometry/Difference.h>
#include <quant/framed_geometry/forward_declarations.h>
#include <quant/framed_units/velocity/forward_declarations.h>
#include <quant/units/velocity/LinearVelocityDifference.h>

#include <ostream>

namespace quant::framed_units::velocity
{

    class LinearVelocityDifference : public FramedDifference<units::velocity::LinearVelocityDifference>
    {
    public:
        using Difference::Difference;
    };
}  // namespace quant::framed_units::velocity
