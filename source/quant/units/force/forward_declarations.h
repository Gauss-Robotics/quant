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

namespace quant
{

    using units::force::Force;
    using units::force::Torque;
    using units::force::Wrench;

    using units::force::ForceDifference;
    using units::force::TorqueDifference;
    using units::force::WrenchDifference;

}  // namespace quant

namespace quant::traits
{

    using ForceDomain = Define3DDomain<Define3DSubDomain<Force, ForceDifference, R3Type>,
                                       Define3DSubDomain<Torque, TorqueDifference, R3Type>,
                                       Define3DSubDomain<Wrench, WrenchDifference, R6Type>>;

    template <>
    struct DefineTraits<Force>
    {
        using Domain = ForceDomain;
        using State = Force;
        using Difference = ForceDifference;
        using GeometricType = LinearStateType;
    };

    template <>
    struct DefineTraits<ForceDifference>
    {
        using Domain = ForceDomain;
        using State = Force;
        using Difference = ForceDifference;
        using GeometricType = LinearDifferenceType;
    };

    template <>
    struct DefineTraits<Torque>
    {
        using Domain = ForceDomain;
        using State = Torque;
        using Difference = TorqueDifference;
        using GeometricType = AngularStateType;
    };

    template <>
    struct DefineTraits<TorqueDifference>
    {
        using Domain = ForceDomain;
        using State = Torque;
        using Difference = TorqueDifference;
        using GeometricType = AngularDifferenceType;
    };

    template <>
    struct DefineTraits<Wrench>
    {
        using Domain = ForceDomain;
        using State = Wrench;
        using Difference = WrenchDifference;
        using GeometricType = SpatialStateType;
    };

    template <>
    struct DefineTraits<WrenchDifference>
    {
        using Domain = ForceDomain;
        using State = Wrench;
        using Difference = WrenchDifference;
        using GeometricType = SpatialDifferenceType;
    };

}  // namespace quant::traits
