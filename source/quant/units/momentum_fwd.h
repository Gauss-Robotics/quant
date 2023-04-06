#pragma once

namespace quant::units::momentum
{

    class LinearMomentum;
    class AngularMomentum;
    class SpatialMomentum;

    class LinearMomentumDifference;
    class AngularMomentumDifference;
    class SpatialMomentumDifference;

    struct Domain
    {
        using LinearState = LinearMomentum;
        using AngularState = AngularMomentum;
        using SpatialState = SpatialMomentum;
        using LinearDifference = LinearMomentumDifference;
        using AngularDifference = AngularMomentumDifference;
        using SpatialDifference = SpatialMomentumDifference;
    };

}  // namespace quant::units::momentum

namespace quant
{

    using units::momentum::AngularMomentum;
    using units::momentum::LinearMomentum;
    using units::momentum::SpatialMomentum;

    using units::momentum::AngularMomentumDifference;
    using units::momentum::LinearMomentumDifference;
    using units::momentum::SpatialMomentumDifference;

}  // namespace quant
