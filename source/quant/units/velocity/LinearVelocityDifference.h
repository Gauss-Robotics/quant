#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/velocity/LinearVelocity.h>
#include <quant/units/velocity_fwd.h>

namespace quant::geometry
{

    template <>
    struct DefineDifferenceType<LinearVelocity>
    {
        using DifferenceType = units::velocity::LinearVelocityDifference;
    };

}  // namespace quant::geometry

namespace quant::units::velocity
{

    class LinearVelocityDifference : public LinearDifference<LinearVelocity>
    {

    public:
        LinearVelocityDifference() : LinearDifference<LinearVelocity>()
        {
            ;
        }

        explicit LinearVelocityDifference(LinearVelocity const& t) :
            LinearDifference<LinearVelocity>(t)
        {
            ;
        }
    };

}  // namespace quant::units::velocity

namespace quant
{

    using units::velocity::LinearVelocityDifference;

}