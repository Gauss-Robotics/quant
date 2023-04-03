#pragma once

#include <iomanip>
#include <string>

namespace quant::units::time::detail
{

    constexpr double int_rounding_offset = 0.5;

    constexpr double d2h = 24;
    constexpr double h2m = 60;
    constexpr double m2s = 60;
    constexpr double s2ms = 1'000;
    constexpr double ms2us = 1'000;
    constexpr double us2ms = 1. / ms2us;
    constexpr double ms2s = 1. / s2ms;
    constexpr double s2m = 1. / m2s;
    constexpr double m2h = 1. / h2m;
    constexpr double h2d = 1. / d2h;

    constexpr double s2us = s2ms * ms2us;
    constexpr double m2us = m2s * s2us;
    constexpr double h2us = h2m * m2us;
    constexpr double d2us = d2h * h2us;
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
        micro_seconds(double micro_seconds)
        {
            return TimePointOrDuration::micro_seconds(micro_seconds);
        }

        /**
         * @brief Constructs a time point or duration from milliseconds.
         * @param milliSeconds Amount of milliseconds.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        milli_seconds(double milli_seconds)
        {
            return TimePointOrDuration::micro_seconds(milli_seconds * ms2us);
        }

        /**
         * @brief Constructs a time point or duration from seconds.
         * @param seconds Amount of seconds.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        seconds(double seconds)
        {
            return TimePointOrDuration::micro_seconds(seconds * s2us);
        }

        /**
         * @brief Constructs a time point or duration from minutes.
         * @param minutes Amount of minutes.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        minutes(double minutes)
        {
            return TimePointOrDuration::micro_seconds(minutes * m2us);
        }

        /**
         * @brief Constructs a time point or duration from hours.
         * @param hours Amount of hours.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        hours(double hours)
        {
            return TimePointOrDuration::micro_seconds(hours * h2us);
        }

        /**
         * @brief Constructs a time point or duration from days.
         * @param days Amount of days.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        days(double days)
        {
            return TimePointOrDuration::micro_seconds(days * d2us);
        }

        /**
         * @brief Returns the amount of microseconds.
         * @return Amount of microseconds.
         */
        double
        to_micro_seconds() const
        {
            return static_cast<TimePointOrDuration const&>(*this).to_micro_seconds();
        }

        /**
         * @brief Returns the amount of milliseconds.
         * @return Amount of milliseconds.
         */
        double
        to_milli_seconds() const
        {
            return static_cast<TimePointOrDuration const&>(*this).to_micro_seconds() * us2ms;
        }

        /**
         * @brief Returns the amount of seconds.
         * @return Amount of seconds.
         */
        double
        to_seconds() const
        {
            return static_cast<TimePointOrDuration const&>(*this).to_micro_seconds() * us2s;
        }

        /**
         * @brief Returns the amount of minutes.
         * @return Amount of minutes.
         */
        double
        to_minutes() const
        {
            return static_cast<TimePointOrDuration const&>(*this).to_micro_seconds() * us2m;
        }

        /**
         * @brief Returns the amount of hours.
         * @return Amount of hours.
         */
        double
        to_hours() const
        {
            return static_cast<TimePointOrDuration const&>(*this).to_micro_seconds() * us2h;
        }

        /**
         * @brief Returns the amount of days.
         * @return Amount of days.
         */
        double
        to_days() const
        {
            return static_cast<TimePointOrDuration const&>(*this).to_micro_seconds() * us2d;
        }

    protected:
        std::string
        to_quantity_unit_string() const
        {
            using namespace detail;

            double time_count = static_cast<TimePointOrDuration const&>(*this).to_micro_seconds();
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
        to_quantity_unit_string(std::string const& format) const
        {
            using namespace detail;

            constexpr size_t string_buffer_size = 32;
            /*
                        const std::int64_t usec =
                            static_cast<TimePointOrDuration const&>(*this).to_micro_seconds();
                        const std::int64_t usec_remainder = usec % 1'000'000;
                        auto const msec = static_cast<std::int64_t>(
                            (static_cast<double>(usec_remainder) * us2ms) + int_rounding_offset);
                        auto const time = static_cast<time_t>(static_cast<double>(usec) /
               1'000'000);

                        struct tm tr;
                        localtime_r(&time, &tr);

                        char buf[string_buffer_size];
                        if (strftime(buf, sizeof(buf), format.c_str(), &tr) == 0)
                        {
                            return "";
                        }
            */
            std::string postformat;
            // postformat = quant::alg::replace_all(postformat, "%msec", std::to_string(msec));
            // postformat =
            //     quant::alg::replace_all(postformat, "%usec", std::to_string(usecRemainder));
            return postformat;
        }
    };

}  // namespace quant::units::time::detail
