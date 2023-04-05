#pragma once

#include <quant/units/time_constants.h>

#include <iomanip>
#include <sstream>
#include <string_view>

namespace quant::units::time::detail
{

    constexpr double int_rounding_offset = 0.5;

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
        microseconds(double microseconds)
        {
            return TimePointOrDuration::microseconds(microseconds);
        }

        /**
         * @brief Constructs a time point or duration from milliseconds.
         * @param milliSeconds Amount of milliseconds.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        milliseconds(double milliseconds)
        {
            return TimePointOrDuration::microseconds(milliseconds * constants::ms2us);
        }

        /**
         * @brief Constructs a time point or duration from seconds.
         * @param seconds Amount of seconds.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        seconds(double seconds)
        {
            return TimePointOrDuration::microseconds(seconds * constants::s2us);
        }

        /**
         * @brief Constructs a time point or duration from minutes.
         * @param minutes Amount of minutes.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        minutes(double minutes)
        {
            return TimePointOrDuration::microseconds(minutes * constants::m2us);
        }

        /**
         * @brief Constructs a time point or duration from hours.
         * @param hours Amount of hours.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        hours(double hours)
        {
            return TimePointOrDuration::microseconds(hours * constants::h2us);
        }

        /**
         * @brief Constructs a time point or duration from days.
         * @param days Amount of days.
         * @return TimePoint or Duration instance.
         */
        static TimePointOrDuration
        days(double days)
        {
            return TimePointOrDuration::microseconds(days * constants::d2us);
        }

        /**
         * @brief Returns the amount of microseconds.
         * @return Amount of microseconds.
         */
        double
        to_microseconds() const
        {
            return static_cast<TimePointOrDuration const&>(*this).to_microseconds();
        }

        /**
         * @brief Returns the amount of milliseconds.
         * @return Amount of milliseconds.
         */
        double
        to_milliseconds() const
        {
            return static_cast<TimePointOrDuration const&>(*this).to_microseconds() *
                   constants::us2ms;
        }

        /**
         * @brief Returns the amount of seconds.
         * @return Amount of seconds.
         */
        double
        to_seconds() const
        {
            return static_cast<TimePointOrDuration const&>(*this).to_microseconds() *
                   constants::us2s;
        }

        /**
         * @brief Returns the amount of minutes.
         * @return Amount of minutes.
         */
        double
        to_minutes() const
        {
            return static_cast<TimePointOrDuration const&>(*this).to_microseconds() *
                   constants::us2m;
        }

        /**
         * @brief Returns the amount of hours.
         * @return Amount of hours.
         */
        double
        to_hours() const
        {
            return static_cast<TimePointOrDuration const&>(*this).to_microseconds() *
                   constants::us2h;
        }

        /**
         * @brief Returns the amount of days.
         * @return Amount of days.
         */
        double
        to_days() const
        {
            return static_cast<TimePointOrDuration const&>(*this).to_microseconds() *
                   constants::us2d;
        }

    protected:
        std::string
        to_quantity_unit_string() const
        {
            double time_count = static_cast<TimePointOrDuration const&>(*this).to_microseconds();
            std::string_view unit = constants::microseconds;

            if (time_count >= constants::ms2us)
            {
                time_count *= constants::us2ms;
                unit = constants::milliseconds;

                if (time_count >= constants::s2ms)
                {
                    time_count *= constants::ms2s;
                    unit = constants::seconds;

                    if (time_count >= constants::m2s)
                    {
                        time_count *= constants::s2m;
                        unit = constants::minutes;

                        if (time_count >= constants::h2m)
                        {
                            time_count *= constants::m2h;
                            unit = constants::hours;

                            if (time_count >= constants::d2h)
                            {
                                time_count *= constants::h2d;
                                unit = constants::days;
                            }
                        }
                    }
                }
            }

            std::stringstream ss;
            ss << std::setprecision(3) << time_count << unit;
            return ss.str();
        }

        std::string
        to_quantity_unit_string(std::string const& format) const
        {
            using namespace detail;

            constexpr size_t string_buffer_size = 32;
            /*
                        const std::int64_t usec =
                            static_cast<TimePointOrDuration const&>(*this).to_microseconds();
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
