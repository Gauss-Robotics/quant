#pragma once


namespace simox::core::time
{
    enum class ClockType;
    class Clock;
    class DateTime;
    class TimePoint;
    class Frequency;
    class Metronome;
    class ScopedStopWatch;
    class StopWatch;
} // namespace simox::core::time

namespace simox
{
    using core::time::Clock;
    using core::time::ClockType;
    using core::time::DateTime;
    using core::time::Frequency;
    using core::time::Metronome;
    using core::time::TimePoint;
} // namespace simox
