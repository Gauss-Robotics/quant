#pragma once

#include <quant/geometry_fwd.h>

namespace quant::units::time
{

    class TimePoint;
    class Duration;
    class Frequency;

    struct Domain
    {
        using State = TimePoint;
        using Difference = Duration;
    };

}  // namespace quant::units::time

namespace quant::traits
{

    template <>
    struct DefineDifferenceTypeOf<units::time::TimePoint>
    {
        using DifferenceType = units::time::Duration;
    };

    template <>
    struct DefineStateTypeOf<units::time::Duration>
    {
        using StateType = units::time::TimePoint;
    };

}  // namespace quant::traits

namespace quant
{

    using units::time::Duration;
    using units::time::Frequency;
    using units::time::TimePoint;

}  // namespace quant
