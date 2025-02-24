#pragma once

#include <quant/geometry/forward_declarations.h>

namespace quant::units::time
{

    class TimePoint;
    class Duration;
    class Frequency;

}  // namespace quant::units::time

namespace quant::traits
{

    using TimeDomain =
        Define1DDomain<units::time::TimePoint, units::time::Duration, R1Type>;

    template <>
    struct DefineTraits<units::time::TimePoint>
    {
        using Domain = TimeDomain;
        using Difference = units::time::Duration;
        using State = units::time::TimePoint;
        using GeometricType = ScalarStateType;
    };

    template <>
    struct DefineTraits<units::time::Duration>
    {
        using Domain = TimeDomain;
        using Difference = units::time::Duration;
        using State = units::time::TimePoint;
        using GeometricType = ScalarDifferenceType;
    };

}  // namespace quant::traits

namespace quant
{

    using units::time::Duration;
    using units::time::Frequency;
    using units::time::TimePoint;

}  // namespace quant
