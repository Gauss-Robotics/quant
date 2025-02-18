#pragma once

#include <quant/geometry/forward_declarations.h>

namespace quant::units::speed
{

    class Speed;
    class SpeedDifference;

}  // namespace quant::units::speed

namespace quant::traits
{
    using SpeedDomain = Define1DDomain<units::speed::Speed, units::speed::SpeedDifference, R1Type>;

    template <>
    struct DefineTraits<units::speed::Speed>
    {
        using Domain = SpeedDomain;
        using State = units::speed::Speed;
        using Difference = units::speed::SpeedDifference;
        using GeometricType = ScalarStateType;
    };

    template <>
    struct DefineTraits<units::speed::SpeedDifference>
    {
        using Domain = SpeedDomain;
        using State = units::speed::Speed;
        using Difference = units::speed::SpeedDifference;
        using GeometricType = ScalarDifferenceType;
    };
}  // namespace quant::traits

namespace quant
{

    using units::speed::Speed;
    using units::speed::SpeedDifference;

}  // namespace quant
