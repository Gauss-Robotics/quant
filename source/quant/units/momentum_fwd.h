#pragma once

namespace quant::units::momentum
{

    class LinearMomentum;
    class AngularMomentum;
    class SpatialMomentum;

    class LinearImpulse;
    class AngularImpulse;
    class SpatialImpulse;

    struct Domain
    {
        using LinearState = LinearMomentum;
        using AngularState = AngularMomentum;
        using SpatialState = SpatialMomentum;
        using LinearDifference = LinearImpulse;
        using AngularDifference = AngularImpulse;
        using SpatialDifference = SpatialImpulse;
    };

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
