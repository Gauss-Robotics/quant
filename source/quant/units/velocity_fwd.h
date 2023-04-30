#pragma once

#include <quant/geometry_fwd.h>

namespace quant::units::velocity
{

    class LinearVelocity;
    class AngularVelocity;
    class Twist;

    class LinearVelocityDifference;
    class AngularVelocityDifference;
    class TwistDifference;

}  // namespace quant::units::velocity

namespace quant::traits
{

    using VelocityDomain = Define3DDomain<units::velocity::LinearVelocity,
                                          units::velocity::AngularVelocity,
                                          units::velocity::Twist,
                                          units::velocity::LinearVelocityDifference,
                                          units::velocity::AngularVelocityDifference,
                                          units::velocity::TwistDifference>;

    template <>
    struct DefineTraits<units::velocity::LinearVelocity>
    {
        using Domain = VelocityDomain;
        using Difference = units::velocity::LinearVelocityDifference;
    };

    template <>
    struct DefineTraits<units::velocity::LinearVelocityDifference>
    {
        using Domain = VelocityDomain;
        using State = units::velocity::LinearVelocity;
    };

    template <>
    struct DefineTraits<units::velocity::AngularVelocity>
    {
        using Domain = VelocityDomain;
        using Difference = units::velocity::AngularVelocityDifference;
    };

    template <>
    struct DefineTraits<units::velocity::AngularVelocityDifference>
    {
        using Domain = VelocityDomain;
        using State = units::velocity::AngularVelocity;
    };

    template <>
    struct DefineTraits<units::velocity::Twist>
    {
        using Domain = VelocityDomain;
        using Difference = units::velocity::TwistDifference;
    };

    template <>
    struct DefineTraits<units::velocity::TwistDifference>
    {
        using Domain = VelocityDomain;
        using State = units::velocity::Twist;
    };

}  // namespace quant::traits

namespace quant
{

    using units::velocity::AngularVelocity;
    using units::velocity::LinearVelocity;
    using units::velocity::Twist;

    using units::velocity::AngularVelocityDifference;
    using units::velocity::LinearVelocityDifference;
    using units::velocity::TwistDifference;

}  // namespace quant
