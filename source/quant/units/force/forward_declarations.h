#pragma once

#include <quant/geometry/forward_declarations.h>

namespace quant::units::force
{

    class Force;
    class Torque;
    class Wrench;

    class ForceDifference;
    class TorqueDifference;
    class WrenchDifference;

}  // namespace quant::units::force

namespace quant::traits
{

    using ForceDomain = Define3DDomain<units::force::Force,
                                       units::force::Torque,
                                       units::force::Wrench,
                                       units::force::ForceDifference,
                                       units::force::TorqueDifference,
                                       units::force::WrenchDifference>;

    template <>
    struct DefineTraits<units::force::Force>
    {
        using Domain = ForceDomain;
        using State = units::force::Force;
        using Difference = units::force::ForceDifference;
        using GeometricType = LinearStateType;
    };

    template <>
    struct DefineTraits<units::force::ForceDifference>
    {
        using Domain = ForceDomain;
        using State = units::force::Force;
        using Difference = units::force::ForceDifference;
        using GeometricType = LinearDifferenceType;
    };

    template <>
    struct DefineTraits<units::force::Torque>
    {
        using Domain = ForceDomain;
        using State = units::force::Torque;
        using Difference = units::force::TorqueDifference;
        using GeometricType = AngularStateType;
    };

    template <>
    struct DefineTraits<units::force::TorqueDifference>
    {
        using Domain = ForceDomain;
        using State = units::force::Torque;
        using Difference = units::force::TorqueDifference;
        using GeometricType = AngularDifferenceType;
    };

    template <>
    struct DefineTraits<units::force::Wrench>
    {
        using Domain = ForceDomain;
        using State = units::force::Wrench;
        using Difference = units::force::WrenchDifference;
        using GeometricType = SpatialStateType;
    };

    template <>
    struct DefineTraits<units::force::WrenchDifference>
    {
        using Domain = ForceDomain;
        using State = units::force::Wrench;
        using Difference = units::force::WrenchDifference;
        using GeometricType = SpatialDifferenceType;
    };

}  // namespace quant::traits

namespace quant
{

    using units::force::Force;
    using units::force::Torque;
    using units::force::Wrench;

    using units::force::ForceDifference;
    using units::force::TorqueDifference;
    using units::force::WrenchDifference;

}  // namespace quant
