#pragma once

#include <quant/geometry/forward_declarations.h>

namespace quant::units::velocity
{

    class LinearVelocity;
    class AngularVelocity;
    class Twist;

    class LinearVelocityDifference;
    class AngularVelocityDifference;
    class TwistDifference;

}  // namespace quant::units::velocity

namespace quant
{

    using units::velocity::AngularVelocity;
    using units::velocity::LinearVelocity;
    using units::velocity::Twist;

    using units::velocity::AngularVelocityDifference;
    using units::velocity::LinearVelocityDifference;
    using units::velocity::TwistDifference;

}  // namespace quant

namespace quant::traits
{

    using VelocityDomain = Define3DDomain<
        Define3DSubDomain<LinearVelocity,
                          LinearVelocityDifference,
                          R3Type>,
        Define3DSubDomain<AngularVelocity,
                          AngularVelocityDifference,
                          R3Type>,
        Define3DSubDomain<Twist, TwistDifference, R6Type>>;

    template <>
    struct DefineTraits<LinearVelocity>
    {
        using Domain = VelocityDomain;
        using State = LinearVelocity;
        using Difference = LinearVelocityDifference;
        using GeometricType = LinearStateType;
    };

    template <>
    struct DefineTraits<LinearVelocityDifference>
    {
        using Domain = VelocityDomain;
        using State = LinearVelocity;
        using Difference = LinearVelocityDifference;
        using GeometricType = LinearDifferenceType;
    };

    template <>
    struct DefineTraits<AngularVelocity>
    {
        using Domain = VelocityDomain;
        using State = AngularVelocity;
        using Difference = AngularVelocityDifference;
        using GeometricType = AngularStateType;
    };

    template <>
    struct DefineTraits<AngularVelocityDifference>
    {
        using Domain = VelocityDomain;
        using State = AngularVelocity;
        using Difference = AngularVelocityDifference;
        using GeometricType = AngularDifferenceType;
    };

    template <>
    struct DefineTraits<Twist>
    {
        using Domain = VelocityDomain;
        using State = Twist;
        using Difference = TwistDifference;
        using GeometricType = SpatialStateType;
    };

    template <>
    struct DefineTraits<TwistDifference>
    {
        using Domain = VelocityDomain;
        using State = Twist;
        using Difference = TwistDifference;
        using GeometricType = SpatialDifferenceType;
    };

}  // namespace quant::traits

