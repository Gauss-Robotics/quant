#pragma once

#include <quant/framed_geometry/Difference.h>
#include <quant/framed_geometry/forward_declarations.h>
#include <quant/framed_units/velocity/forward_declarations.h>
#include <quant/units/velocity/TwistDifference.h>

#include <ostream>

namespace quant::framed_units::velocity
{

    class TwistDifference : public FramedDifference<units::velocity::TwistDifference>
    {
    public:
        using Difference::Difference;
    };
}  // namespace quant::framed_units::velocity
