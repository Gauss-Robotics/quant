#pragma once

#include <quant/framed_geometry/Difference.h>
#include <quant/framed_geometry/forward_declarations.h>
#include <quant/framed_units/velocity/forward_declarations.h>
#include <quant/units/velocity/AngularVelocityDifference.h>

#include <ostream>

namespace quant::framed_units::velocity
{

    class AngularVelocityDifference : public FramedDifference<units::velocity::AngularVelocityDifference>
    {
    public:
        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& os, AngularVelocityDifference const& rhs);

}  // namespace quant::framed_units::velocity
