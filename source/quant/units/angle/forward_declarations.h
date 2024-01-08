#pragma once

#include <quant/geometry/forward_declarations.h>

namespace quant::units::angle
{

    class Angle;
    class AngleDifference;

}  // namespace quant::units::angle

namespace quant::traits
{

    using AngleDomain = Define1DDomain<units::angle::Angle, units::angle::AngleDifference>;

    template <>
    struct DefineTraits<units::angle::Angle>
    {
        using Domain = AngleDomain;
        using Difference = units::angle::AngleDifference;
        using GeometricType = ScalarStateType;
    };

    template <>
    struct DefineTraits<units::angle::AngleDifference>
    {
        using Domain = AngleDomain;
        using State = units::angle::Angle;
        using GeometricType = ScalarDifferenceType;
    };

}  // namespace quant::traits

namespace quant
{

    using units::angle::Angle;
    using units::angle::AngleDifference;

}  // namespace quant
