#pragma once

#include <quant/framed_geometry/Difference.h>
#include <quant/units/force/TorqueDifference.h>
#include <quant/framed_units/force/forward_declarations.h>

namespace quant::framed_units::force
{

    class TorqueDifference : public framed_geometry::Difference<units::force::TorqueDifference>
    {
    public:
        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& out, TorqueDifference const& rhs);

}  // namespace quant::framed_units::force
