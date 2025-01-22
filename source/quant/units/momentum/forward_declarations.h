#pragma once

#include <quant/geometry/forward_declarations.h>

namespace quant::units::momentum
{

    class LinearMomentum;
    class AngularMomentum;
    class SpatialMomentum;

    class LinearImpulse;
    class AngularImpulse;
    class SpatialImpulse;

}  // namespace quant::units::momentum

namespace quant::traits
{

    using MomentumDomain = Define3DDomain<units::momentum::LinearMomentum,
                                          units::momentum::AngularMomentum,
                                          units::momentum::SpatialMomentum,
                                          units::momentum::LinearImpulse,
                                          units::momentum::AngularImpulse,
                                          units::momentum::SpatialImpulse>;

    template <>
    struct DefineTraits<units::momentum::LinearMomentum>
    {
        using Domain = MomentumDomain;
        using State = units::momentum::LinearMomentum;
        using Difference = units::momentum::LinearImpulse;
        using GeometricType = LinearStateType;
    };

    template <>
    struct DefineTraits<units::momentum::LinearImpulse>
    {
        using Domain = MomentumDomain;
        using State = units::momentum::LinearMomentum;
        using Difference = units::momentum::LinearImpulse;
        using GeometricType = LinearDifferenceType;
    };

}  // namespace quant::traits

namespace quant
{

    using units::momentum::AngularMomentum;
    using units::momentum::LinearMomentum;
    using units::momentum::SpatialMomentum;

    using units::momentum::AngularImpulse;
    using units::momentum::LinearImpulse;
    using units::momentum::SpatialImpulse;

}  // namespace quant
