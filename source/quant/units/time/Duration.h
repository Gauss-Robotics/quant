#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/Scalar.h>
#include <quant/units/time/TimePoint.h>
#include <quant/units/time_fwd.h>

namespace quant::units::time
{

    /**
     * @brief Represents a duration.
     */
    class Duration : public geometry::Difference<TimePoint>
    {

    public:
        /**
         * @brief Constructs a time point in microseconds.
         * @param microSeconds Amount of microseconds.
         * @return Duration instance.
         */
        static Duration
        microseconds(geometry::Scalar microseconds)
        {
            return Duration{TimePoint::microseconds(microseconds)};
        }

        /**
         * @brief Constructs a duration from milliseconds.
         * @param milliSeconds Amount of milliseconds.
         * @return TimePoint or Duration instance.
         */
        static Duration
        milliseconds(geometry::Scalar milliseconds)
        {
            return Duration{TimePoint::milliseconds(milliseconds)};
        }

        /**
         * @brief Constructs a duration from seconds.
         * @param seconds Amount of seconds.
         * @return TimePoint or Duration instance.
         */
        static Duration
        seconds(geometry::Scalar seconds)
        {
            return Duration{TimePoint::seconds(seconds)};
        }

        /**
         * @brief Constructs a duration from minutes.
         * @param minutes Amount of minutes.
         * @return TimePoint or Duration instance.
         */
        static Duration
        minutes(geometry::Scalar minutes)
        {
            return Duration{TimePoint::minutes(minutes)};
        }

        /**
         * @brief Constructs a duration from hours.
         * @param hours Amount of hours.
         * @return TimePoint or Duration instance.
         */
        static Duration
        hours(geometry::Scalar hours)
        {
            return Duration{TimePoint::hours(hours)};
        }

        /**
         * @brief Constructs a duration from days.
         * @param days Amount of days.
         * @return TimePoint or Duration instance.
         */
        static Duration
        days(geometry::Scalar days)
        {
            return Duration{TimePoint::days(days)};
        }

        /**
         * @brief Returns the amount of microseconds.
         * @return Amount of microseconds.
         */
        Scalar
        to_microseconds() const
        {
            return {_difference_object.to_microseconds(),
                    constants::names::duration,
                    constants::symbols::microseconds};
        }

        /**
         * @brief Returns the amount of milliseconds.
         * @return Amount of milliseconds.
         */
        Scalar
        to_milliseconds() const
        {
            return {_difference_object.to_milliseconds(),
                    constants::names::duration,
                    constants::symbols::milliseconds};
        }

        /**
         * @brief Returns the amount of seconds.
         * @return Amount of seconds.
         */
        Scalar
        to_seconds() const
        {
            return {_difference_object.to_seconds(),
                    constants::names::duration,
                    constants::symbols::seconds};
        }

        /**
         * @brief Returns the amount of minutes.
         * @return Amount of minutes.
         */
        Scalar
        to_minutes() const
        {
            return {_difference_object.to_minutes(),
                    constants::names::duration,
                    constants::symbols::minutes};
        }

        /**
         * @brief Returns the amount of hours.
         * @return Amount of hours.
         */
        Scalar
        to_hours() const
        {
            return {_difference_object.to_hours(),
                    constants::names::duration,
                    constants::symbols::hours};
        }

        /**
         * @brief Returns the amount of days.
         * @return Amount of days.
         */
        Scalar
        to_days() const
        {
            return {
                _difference_object.to_days(), constants::names::duration, constants::symbols::days};
        }

        /**
         * @brief Tests whether the time point is positive (value in µs > 0).
         * @return True if time point is positive, else otherwise.
         */
        bool
        is_positive() const;

        /**
         * @brief Tests whether the time point is zero.
         * @return True if time point is zero, else otherwise.
         */
        bool
        is_zero() const;

        /**
         * @brief String representation of the current duration in minimal/default format.
         *
         * The minimal representation is a float representation with max. 3 decimals. The unit will
         * be determined by the highest unit whose value is non-zero. For example, 3 seconds and 500
         * milliseconds => "3.5s".
         *
         * @return Formatted duration.
         */
        std::string
        to_string() const
        {
            return _difference_object.to_string();
        }

        /**
         * @brief String representation of the current duration according to given format string.
         *
         * The format is according to https://en.cppreference.com/w/cpp/chrono/c/strftime. For
         * milliseconds and microseconds, special specifiers "%%msec" and "%%usec" were added
         * respectively.
         *
         * Example format string for "10m 10.987s": "%Mm %S.%%msecs".
         *
         * @param format Format string.
         * @return Formatted duration.
         */
        std::string
        to_string(std::string const& format) const
        {
            return _difference_object.to_string(format);
        }

    protected:
        using geometry::Difference<TimePoint>::Difference;
    };

    inline std::ostream&
    operator<<(std::ostream& out, Duration const& rhs)
    {
        return out << rhs.to_string();
    }

}  // namespace quant::units::time
