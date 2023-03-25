#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/force/Force.h>
#include <quant/units/force_fwd.h>

namespace quant::geometry
{

    template <>
    struct DefineDifferenceType<Force>
    {
        using DifferenceType = units::force::ForceDifference;
    };

}  // namespace quant::geometry

namespace quant::units::force
{

    class ForceDifference : public LinearDifference<Domain>
    {

    public:
        using LinearDifference<Domain>::LinearDifference;
    };

}  // namespace quant::units::force

namespace quant
{

    using units::force::ForceDifference;

}
