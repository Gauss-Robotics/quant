#pragma once

namespace quant::units::acceleration
{

    class LinearAcceleration;
    class AngularAcceleration;
    class SpatialAcceleration;

    class LinearAccelerationDifference;
    class AngularAccelerationDifference;
    class SpatialAccelerationDifference;

}  // namespace quant::units::acceleration

namespace quant
{

    using units::acceleration::AngularAcceleration;
    using units::acceleration::LinearAcceleration;
    using units::acceleration::SpatialAcceleration;

    using units::acceleration::AngularAccelerationDifference;
    using units::acceleration::LinearAccelerationDifference;
    using units::acceleration::SpatialAccelerationDifference;

}  // namespace quant

namespace quant::traits
{

    using LinearAccelerationDomain = Define3DDomain<
        Define3DSubDomain<LinearAcceleration, LinearAccelerationDifference, R3Type>,
        Define3DSubDomain<AngularAcceleration, AngularAccelerationDifference, R3Type>,
        Define3DSubDomain<SpatialAcceleration, SpatialAccelerationDifference, R6Type>>;

    template <>
    struct DefineTraits<LinearAcceleration>
    {
        using Domain = LinearAccelerationDomain;
        using State = LinearAcceleration;
        using Difference = LinearAccelerationDifference;
        using GeometricType = LinearStateType;
    };

    template <>
    struct DefineTraits<LinearAccelerationDifference>
    {
        using Domain = LinearAccelerationDomain;
        using State = LinearAcceleration;
        using Difference = LinearAccelerationDifference;
        using GeometricType = LinearDifferenceType;
    };

    template <>
    struct DefineTraits<AngularAcceleration>
    {
        using Domain = LinearAccelerationDomain;
        using State = AngularAcceleration;
        using Difference = AngularAccelerationDifference;
        using GeometricType = AngularStateType;
    };

    template <>
    struct DefineTraits<AngularAccelerationDifference>
    {
        using Domain = LinearAccelerationDomain;
        using State = AngularAcceleration;
        using Difference = AngularAccelerationDifference;
        using GeometricType = AngularDifferenceType;
    };

    template <>
    struct DefineTraits<SpatialAcceleration>
    {
        using Domain = LinearAccelerationDomain;
        using State = SpatialAcceleration;
        using Difference = SpatialAccelerationDifference;
        using GeometricType = SpatialStateType;
    };

    template <>
    struct DefineTraits<SpatialAccelerationDifference>
    {
        using Domain = LinearAccelerationDomain;
        using State = SpatialAcceleration;
        using Difference = SpatialAccelerationDifference;
        using GeometricType = SpatialDifferenceType;
    };

}  // namespace quant::traits
