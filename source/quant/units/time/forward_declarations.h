#pragma once


namespace quant::time
{
    enum class ClockType;
    class Clock;
    class DateTime;
    class TimePoint;
    class Frequency;
    class Metronome;
    class ScopedStopWatch;
    class StopWatch;
} // namespace quant::time

namespace quant
{
    using core::time::Clock;
    using core::time::ClockType;
    using core::time::DateTime;
    using core::time::Frequency;
    using core::time::Metronome;
    using core::time::TimePoint;
} // namespace quant
