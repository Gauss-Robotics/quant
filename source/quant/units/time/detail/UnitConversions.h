#pragma once

#include <cstdint>
#include <iomanip>
#include <string>

namespace quant::units::time::detail
{

    constexpr double intRoundingOffset = 0.5;

    constexpr std::int64_t d2h = 24;
    constexpr std::int64_t h2m = 60;
    constexpr std::int64_t m2s = 60;
    constexpr std::int64_t s2ms = 1'000;
    constexpr std::int64_t ms2us = 1'000;
    constexpr double us2ms = 1. / ms2us;
    constexpr double ms2s = 1. / s2ms;
    constexpr double s2m = 1. / m2s;
    constexpr double m2h = 1. / h2m;
    constexpr double h2d = 1. / d2h;

    constexpr std::int64_t s2us = s2ms * ms2us;
    constexpr std::int64_t m2us = m2s * s2us;
    constexpr std::int64_t h2us = h2m * m2us;
    constexpr std::int64_t d2us = d2h * h2us;
    constexpr double us2s = us2ms * ms2s;
    constexpr double us2m = us2s * s2m;
    constexpr double us2h = us2m * m2h;
    constexpr double us2d = us2h * h2d;

    template <typename TimePointOrDuration>
    class UnitConversions
    {
    public:
        /**
         * @brief Constructs a time point or duration from microseconds.
         * @param microSeconds Amount of microseconds.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        microSeconds(int microSeconds)
        {
            return TimePointOrDuration::MicroSeconds(static_cast<std::int64_t>(microSeconds));
        }

        /**
         * @brief Constructs a time point or duration from microseconds.
         * @param microSeconds Amount of microseconds.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        microSeconds(double microSeconds)
        {
            return TimePointOrDuration::MicroSeconds(static_cast<std::int64_t>(microSeconds));
        }

        /**
         * @brief Constructs a time point or duration from milliseconds.
         * @param milliSeconds Amount of milliseconds.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        milliSeconds(std::int64_t milliSeconds)
        {
            return TimePointOrDuration::microSeconds(
                static_cast<std::int64_t>(milliSeconds * ms2us));
        }

        /**
         * @brief Constructs a time point or duration from milliseconds.
         * @param milliSeconds Amount of milliseconds.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        milliSeconds(int milliSeconds)
        {
            return TimePointOrDuration::microSeconds(
                static_cast<std::int64_t>(milliSeconds * ms2us));
        }

        /**
         * @brief Constructs a time point or duration from milliseconds.
         * @param milliSeconds Amount of milliseconds.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        milliSeconds(double milliSeconds)
        {
            return TimePointOrDuration::microSeconds(
                static_cast<std::int64_t>(milliSeconds * ms2us));
        }

        /**
         * @brief Constructs a time point or duration from seconds.
         * @param seconds Amount of seconds.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        seconds(std::int64_t seconds)
        {
            return TimePointOrDuration::microSeconds(static_cast<std::int64_t>(seconds * s2us));
        }

        /**
         * @brief Constructs a time point or duration from seconds.
         * @param seconds Amount of seconds.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        seconds(int seconds)
        {
            return TimePointOrDuration::microSeconds(static_cast<std::int64_t>(seconds * s2us));
        }

        /**
         * @brief Constructs a time point or duration from seconds.
         * @param seconds Amount of seconds.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        seconds(double seconds)
        {
            return TimePointOrDuration::microSeconds(static_cast<std::int64_t>(seconds * s2us));
        }

        /**
         * @brief Constructs a time point or duration from minutes.
         * @param minutes Amount of minutes.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        minutes(std::int64_t minutes)
        {
            return TimePointOrDuration::microSeconds(static_cast<std::int64_t>(minutes * m2us));
        }

        /**
         * @brief Constructs a time point or duration from minutes.
         * @param minutes Amount of minutes.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        minutes(int minutes)
        {
            return TimePointOrDuration::microSeconds(static_cast<std::int64_t>(minutes * m2us));
        }

        /**
         * @brief Constructs a time point or duration from minutes.
         * @param minutes Amount of minutes.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        minutes(double minutes)
        {
            return TimePointOrDuration::microSeconds(static_cast<std::int64_t>(minutes * m2us));
        }

        /**
         * @brief Constructs a time point or duration from hours.
         * @param hours Amount of hours.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        hours(std::int64_t hours)
        {
            return TimePointOrDuration::microSeconds(static_cast<std::int64_t>(hours * h2us));
        }

        /**
         * @brief Constructs a time point or duration from hours.
         * @param hours Amount of hours.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        hours(int hours)
        {
            return TimePointOrDuration::microSeconds(static_cast<std::int64_t>(hours * h2us));
        }

        /**
         * @brief Constructs a time point or duration from hours.
         * @param hours Amount of hours.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        hours(double hours)
        {
            return TimePointOrDuration::microSeconds(static_cast<std::int64_t>(hours * h2us));
        }

        /**
         * @brief Constructs a time point or duration from days.
         * @param days Amount of days.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        days(std::int64_t days)
        {
            return TimePointOrDuration::microSeconds(static_cast<std::int64_t>(days * d2us));
        }

        /**
         * @brief Constructs a time point or duration from days.
         * @param days Amount of days.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        days(int days)
        {
            return TimePointOrDuration::microSeconds(static_cast<std::int64_t>(days * d2us));
        }

        /**
         * @brief Constructs a time point or duration from days.
         * @param days Amount of days.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        days(double days)
        {
            return TimePointOrDuration::microSeconds(static_cast<std::int64_t>(days * d2us));
        }

        /**
         * @brief Returns the amount of microseconds.
         * @return Amount of microseconds.
         */
        double
        toMicroSecondsDouble() const
        {
            return static_cast<TimePointOrDuration const&>(*this).toMicroSeconds();
        }

        /**
         * @brief Returns the amount of milliseconds.
         * @return Amount of milliseconds.
         */
        std::int64_t
        toMilliSeconds() const
        {
            return static_cast<TimePointOrDuration const&>(*this).toMicroSecondsDouble() * us2ms +
                   intRoundingOffset;
        }

        /**
         * @brief Returns the amount of milliseconds.
         * @return Amount of milliseconds.
         */
        double
        toMilliSecondsDouble() const
        {
            return static_cast<TimePointOrDuration const&>(*this).toMicroSecondsDouble() * us2ms;
        }

        /**
         * @brief Returns the amount of seconds.
         * @return Amount of seconds.
         */
        std::int64_t
        toSeconds() const
        {
            return static_cast<TimePointOrDuration const&>(*this).toMicroSecondsDouble() * us2s +
                   intRoundingOffset;
        }

        /**
         * @brief Returns the amount of seconds.
         * @return Amount of seconds.
         */
        double
        toSecondsDouble() const
        {
            return static_cast<TimePointOrDuration const&>(*this).toMicroSecondsDouble() * us2s;
        }

        /**
         * @brief Returns the amount of minutes.
         * @return Amount of minutes.
         */
        std::int64_t
        toMinutes() const
        {
            return static_cast<TimePointOrDuration const&>(*this).toMicroSecondsDouble() * us2m +
                   intRoundingOffset;
        }

        /**
         * @brief Returns the amount of minutes.
         * @return Amount of minutes.
         */
        double
        toMinutesDouble() const
        {
            return static_cast<TimePointOrDuration const&>(*this).toMicroSecondsDouble() * us2m;
        }

        /**
         * @brief Returns the amount of hours.
         * @return Amount of hours.
         */
        std::int64_t
        toHours() const
        {
            return static_cast<TimePointOrDuration const&>(*this).toMicroSecondsDouble() * us2h +
                   intRoundingOffset;
        }

        /**
         * @brief Returns the amount of hours.
         * @return Amount of hours.
         */
        double
        toHoursDouble() const
        {
            return static_cast<TimePointOrDuration const&>(*this).toMicroSecondsDouble() * us2h;
        }

        /**
         * @brief Returns the amount of days.
         * @return Amount of days.
         */
        std::int64_t
        toDays() const
        {
            return static_cast<TimePointOrDuration const&>(*this).toMicroSecondsDouble() * us2d +
                   intRoundingOffset;
        }

        /**
         * @brief Returns the amount of days.
         * @return Amount of days.
         */
        double
        toDaysDouble() const
        {
            return static_cast<TimePointOrDuration const&>(*this).toMicroSecondsDouble() * us2d;
        }

    protected:
        std::string
        toQuantityUnitString() const
        {
            using namespace detail;

            double time_count =
                static_cast<TimePointOrDuration const&>(*this).toMicroSecondsDouble();
            std::string unit = "µs";

            if (time_count >= ms2us)
            {
                time_count *= us2ms;
                unit = "ms";

                if (time_count >= s2ms)
                {
                    time_count *= ms2s;
                    unit = "s";

                    if (time_count >= m2s)
                    {
                        time_count *= s2m;
                        unit = "min";

                        if (time_count >= h2m)
                        {
                            time_count *= m2h;
                            unit = "h";

                            if (time_count >= d2h)
                            {
                                time_count *= h2d;
                                unit = "d";
                            }
                        }
                    }
                }
            }

            std::stringstream ss;
            ss << std::setprecision(3) << time_count;
            return ss.str() + unit;
        }

        std::string
        toQuantityUnitString(std::string const& format) const
        {
            using namespace detail;

            constexpr size_t stringBufferSize = 32;

            const std::int64_t usec =
                static_cast<TimePointOrDuration const&>(*this).toMicroSeconds();
            const std::int64_t usecRemainder = usec % 1'000'000;
            auto const msec = static_cast<std::int64_t>(
                (static_cast<double>(usecRemainder) * us2ms) + intRoundingOffset);
            auto const time = static_cast<time_t>(static_cast<double>(usec) / 1'000'000);

            struct tm tr;
            localtime_r(&time, &tr);

            char buf[stringBufferSize];
            if (strftime(buf, sizeof(buf), format.c_str(), &tr) == 0)
            {
                return "";
            }

            std::string postformat(buf);
            // postformat = quant::alg::replace_all(postformat, "%msec", std::to_string(msec));
            // postformat =
            //     quant::alg::replace_all(postformat, "%usec", std::to_string(usecRemainder));
            return postformat;
        }
    };

}  // namespace quant::units::time::detail
