#pragma once

#include <quant/framed_geometry/Difference.h>
#include <quant/units/force/ForceDifference.h>
#include <quant/framed_units/force/forward_declarations.h>

namespace quant::framed_units::force
{

    class ForceDifference : public framed_geometry::Difference<units::force::ForceDifference>
    {

    public:
        using Difference::Difference;
    };
}  // namespace quant::framed_units::force
