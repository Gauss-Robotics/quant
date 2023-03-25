#pragma once

namespace quant::units::velocity
{

    class LinearVelocity;
    class AngularVelocity;
    class Twist;
    class LinearVelocityDifference;
    class AngularVelocityDifference;
    class TwistDifference;

    struct Domain
    {
        using LinearState = LinearVelocity;
        using AngularState = AngularVelocity;
        using SpatialState = Twist;
        using LinearDifference = LinearVelocityDifference;
        using AngularDifference = AngularVelocityDifference;
        using SpatialDifference = TwistDifference;
    };

}  // namespace quant::units::velocity

namespace quant
{

    using units::velocity::AngularVelocity;
    using units::velocity::AngularVelocityDifference;
    using units::velocity::LinearVelocity;
    using units::velocity::LinearVelocityDifference;
    using units::velocity::Twist;

}  // namespace quant
