#pragma once

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

namespace quant
{

    using units::time::Duration;
    using units::time::Frequency;
    using units::time::TimePoint;

}  // namespace quant
