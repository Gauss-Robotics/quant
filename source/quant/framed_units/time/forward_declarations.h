#pragma once

#include <quant/framed_geometry/forward_declarations.h>
#include <quant/geometry/forward_declarations.h>
#include <quant/units/time/forward_declarations.h>

namespace quant::framed_units::time
{

    class TimePoint;
    class Duration;
    class DateTime;
    class Frequency;

    namespace measurement
    {

        class ClockInterface;
        class Clock;

    }  // namespace measurement

}  // namespace quant::framed_units::time

namespace quant::traits
{

    using FramedTimeDomain =
        Define1DDomain<framed_units::time::TimePoint, framed_units::time::Duration>;

    template <>
    struct DefineFramedTraits<units::time::TimePoint> : public traits_of<units::time::TimePoint>
    {
        using FramedDomain = FramedTimeDomain;
        using Framed = framed_units::time::TimePoint;
        using FramedDifference = framed_units::time::Duration;
    };

    template <>
    struct DefineFramedTraits<units::time::Duration> : public traits_of<units::time::Duration>
    {
        using FramedDomain = FramedTimeDomain;
        using Framed = framed_units::time::Duration;
        using FramedState = framed_units::time::TimePoint;
    };

}  // namespace quant::traits

namespace quant
{

    using framed_units::time::DateTime;
    using FramedDuration = framed_units::time::Duration;
    using FramedFrequency = framed_units::time::Frequency;
    using FramedTimePoint = framed_units::time::TimePoint;
    using framed_units::time::measurement::Clock;
    using framed_units::time::measurement::ClockInterface;

}  // namespace quant
