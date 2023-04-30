#pragma once

#include <quant/geometry_fwd.h>

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
        using Difference = units::momentum::LinearImpulse;
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
