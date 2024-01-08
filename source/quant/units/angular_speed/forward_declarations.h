#pragma once

#include <quant/geometry/forward_declarations.h>

namespace quant::units::angular_speed
{

    class AngularSpeed;
    class AngularSpeedDifference;

}  // namespace quant::units::angular_speed

namespace quant::traits
{

    using AngularSpeedDomain = Define1DDomain<units::angular_speed::AngularSpeed,
                                              units::angular_speed::AngularSpeedDifference>;

    template <>
    struct DefineTraits<units::angular_speed::AngularSpeed>
    {
        using Domain = AngularSpeedDomain;
        using Difference = units::angular_speed::AngularSpeedDifference;
        using GeometricType = ScalarStateType;
    };

    template <>
    struct DefineTraits<units::angular_speed::AngularSpeedDifference>
    {
        using Domain = AngularSpeedDomain;
        using State = units::angular_speed::AngularSpeed;
        using GeometricType = ScalarDifferenceType;
    };

}  // namespace quant::traits

namespace quant
{

    using units::angular_speed::AngularSpeed;
    using units::angular_speed::AngularSpeedDifference;

}  // namespace quant
