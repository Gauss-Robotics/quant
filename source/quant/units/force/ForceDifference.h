#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/force/Force.h>
#include <quant/units/force/forward_declarations.h>

namespace quant::units::force
{

    class ForceDifference : public geometry::Difference<Force>
    {

    public:
        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& os, ForceDifference const& rhs);

}  // namespace quant::units::force
