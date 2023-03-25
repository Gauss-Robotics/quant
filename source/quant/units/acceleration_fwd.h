#pragma once

namespace quant::units::acceleration
{

    class LinearAcceleration;
    class AngularAcceleration;
    class SpatialAcceleration;
    class LinearAccelerationDifference;
    class AngularAccelerationDifference;
    class SpatialAccelerationDifference;

    struct Domain
    {
        using LinearState = LinearAcceleration;
        using AngularState = AngularAcceleration;
        using SpatialState = SpatialAcceleration;
        using LinearDifference = LinearAccelerationDifference;
        using AngularDifference = AngularAccelerationDifference;
        using SpatialDifference = SpatialAccelerationDifference;
    };

}  // namespace quant::units::acceleration

namespace quant
{

    using units::acceleration::AngularAcceleration;
    using units::acceleration::AngularAccelerationDifference;
    using units::acceleration::LinearAcceleration;
    using units::acceleration::LinearAccelerationDifference;
    using units::acceleration::SpatialAcceleration;
    using units::acceleration::SpatialAccelerationDifference;

}  // namespace quant
