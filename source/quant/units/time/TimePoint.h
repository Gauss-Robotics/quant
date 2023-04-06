#pragma once

#include <quant/geometry/ScalarState.h>
#include <quant/units/Scalar.h>
#include <quant/units/time_constants.h>
#include <quant/units/time_fwd.h>

#include <iomanip>
#include <ostream>
#include <string>

namespace quant::units::time
{

    /**
     * @brief Represents a time point.
     */
    class TimePoint : public geometry::ScalarState<Domain>
    {
        // Construct.
    public:
        /**
         * @brief Constructs a time point in microseconds.
         * @param microSeconds Amount of microseconds.
         * @return TimePoint instance.
         */
        static TimePoint
        microseconds(geometry::Scalar microseconds)
        {
            return {microseconds};
        }

        /**
         * @brief Constructs a time point from milliseconds.
         * @param milliSeconds Amount of milliseconds.
         * @return TimePoint or Duration instance.
         */
        static TimePoint
        milliseconds(geometry::Scalar milliseconds)
        {
            return {milliseconds * constants::ms2us};
        }

        /**
         * @brief Constructs a time point from seconds.
         * @param seconds Amount of seconds.
         * @return TimePoint or Duration instance.
         */
        static TimePoint
        seconds(geometry::Scalar seconds)
        {
            return {seconds * constants::s2us};
        }

        /**
         * @brief Constructs a time point from minutes.
         * @param minutes Amount of minutes.
         * @return TimePoint or Duration instance.
         */
        static TimePoint
        minutes(geometry::Scalar minutes)
        {
            return {minutes * constants::min2us};
        }

        /**
         * @brief Constructs a time point from hours.
         * @param hours Amount of hours.
         * @return TimePoint or Duration instance.
         */
        static TimePoint
        hours(geometry::Scalar hours)
        {
            return {hours * constants::h2us};
        }

        /**
         * @brief Constructs a time point from days.
         * @param days Amount of days.
         * @return TimePoint or Duration instance.
         */
        static TimePoint
        days(geometry::Scalar days)
        {
            return {days * constants::d2us};
        }

        /**
         * @brief Returns the amount of microseconds.
         * @return Amount of microseconds.
         */
        Scalar
        to_microseconds() const
        {
            return {
                _representation, constants::names::time_point, constants::symbols::microseconds};
        }

        /**
         * @brief Returns the amount of milliseconds.
         * @return Amount of milliseconds.
         */
        Scalar
        to_milliseconds() const
        {
            return {_representation * constants::us2ms,
                    constants::names::time_point,
                    constants::symbols::milliseconds};
        }

        /**
         * @brief Returns the amount of seconds.
         * @return Amount of seconds.
         */
        Scalar
        to_seconds() const
        {
            return {_representation * constants::us2s,
                    constants::names::time_point,
                    constants::symbols::seconds};
        }

        /**
         * @brief Returns the amount of minutes.
         * @return Amount of minutes.
         */
        Scalar
        to_minutes() const
        {
            return {_representation * constants::us2min,
                    constants::names::time_point,
                    constants::symbols::minutes};
        }

        /**
         * @brief Returns the amount of hours.
         * @return Amount of hours.
         */
        Scalar
        to_hours() const
        {
            return {_representation * constants::us2h,
                    constants::names::time_point,
                    constants::symbols::hours};
        }

        /**
         * @brief Returns the amount of days.
         * @return Amount of days.
         */
        Scalar
        to_days() const
        {
            return {_representation * constants::us2d,
                    constants::names::time_point,
                    constants::symbols::days};
        }

        /**
         * @brief Tests whether the time point is positive (value in µs > 0).
         * @return True if time point is positive, else otherwise.
         */
        bool
        is_positive() const
        {
            return _representation > 0;
        }

        /**
         * @brief Tests whether the time point is zero.
         * @return True if time point is zero, else otherwise.
         */
        bool
        is_zero() const
        {
            return _representation == 0;
        }

        /**
         * @brief String representation of the current time point in minimal/default format.
         *
         * The minimal representation is a float representation with max. 3 decimals. The unit will
         * be determined by the highest unit whose value is non-zero. For example, 3 seconds and 500
         * milliseconds => "3.5s".
         *
         * @return Formatted time point.
         */
        std::string
        to_time_point_string() const
        {
            double time_count = to_microseconds();
            std::string_view unit = constants::symbols::microseconds;

            if (time_count >= constants::ms2us)
            {
                time_count *= constants::us2ms;
                unit = constants::symbols::milliseconds;

                if (time_count >= constants::s2ms)
                {
                    time_count *= constants::ms2s;
                    unit = constants::symbols::seconds;

                    if (time_count >= constants::min2s)
                    {
                        time_count *= constants::s2min;
                        unit = constants::symbols::minutes;

                        if (time_count >= constants::h2min)
                        {
                            time_count *= constants::min2h;
                            unit = constants::symbols::hours;

                            if (time_count >= constants::d2h)
                            {
                                time_count *= constants::h2d;
                                unit = constants::symbols::days;
                            }
                        }
                    }
                }
            }

            std::stringstream ss;
            ss << std::setprecision(3) << time_count << unit;
            return ss.str();
        }

        /**
         * @brief String representation of the current time point according to given format string.
         *
         * The format is according to https://en.cppreference.com/w/cpp/chrono/c/strftime. For
         * milli seconds and micro seconds, special specifiers "%%msec" and "%%usec" were added
         * respectively.
         *
         * Example format string for "10m 10.987s": "%Mm %S.%%msecs".
         *
         * @param format Format string.
         * @return Formatted time point.
         */
        std::string
        to_time_point_string(std::string const& format) const
        {
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

    protected:
        using geometry::ScalarState<Domain>::ScalarState;
    };

    inline std::ostream&
    operator<<(std::ostream& out, TimePoint const& rhs)
    {
        return out << rhs.to_time_point_string();
    }

}  // namespace quant::units::time
