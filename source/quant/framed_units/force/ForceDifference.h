#pragma once

#include <quant/framed_geometry/Difference.h>
#include <quant/units/force/ForceDifference.h>

namespace quant::framed_units::force
{

    class ForceDifference : public framed_geometry::Difference<units::force::ForceDifference>
    {

    public:
        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& os, ForceDifference const& rhs);

}  // namespace quant::framed_units::force
