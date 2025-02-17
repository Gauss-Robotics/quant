#pragma once

#include <quant/framed_geometry/Difference.h>
#include <quant/units/force/WrenchDifference.h>
#include <quant/framed_units/force/forward_declarations.h>

namespace quant::framed_units::force
{

    class WrenchDifference : public framed_geometry::Difference<units::force::WrenchDifference>
    {

    public:
        using Difference::Difference;
    };
}  // namespace quant::framed_units::force
