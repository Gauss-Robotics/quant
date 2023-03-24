#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/Difference.h>
#include <quant/units/velocity/AngularVelocity.h>
#include <quant/units/velocity_fwd.h>

namespace quant::geometry
{

    template <>
    struct DefineDifferenceType<quant::AngularVelocity>
    {
        using DifferenceType = units::velocity::AngularVelocityDifference;
    };

}  // namespace quant::geometry

namespace quant::units::velocity
{

    class AngularVelocityDifference : public AngularDifference<AngularVelocity>
    {

    public:
        using AngularDifference<AngularVelocity>::AngularDifference;
    };

}  // namespace quant::units::velocity

namespace quant
{

    using units::velocity::AngularVelocityDifference;

}  // namespace quant
