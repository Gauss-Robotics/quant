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

namespace quant
{

    using units::momentum::AngularMomentum;
    using units::momentum::LinearMomentum;
    using units::momentum::SpatialMomentum;

    using units::momentum::AngularImpulse;
    using units::momentum::LinearImpulse;
    using units::momentum::SpatialImpulse;

}  // namespace quant

namespace quant::traits
{
    // TODO: are the manifolds correct here?
    using MomentumDomain = Define3DDomain<Define3DSubDomain<LinearMomentum, LinearImpulse, R3Type>,
                                          Define3DSubDomain<AngularMomentum, AngularImpulse, R3Type>,
                                          Define3DSubDomain<SpatialMomentum, SpatialImpulse, R6Type>>;

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