#pragma once

#include <quant/geometry/ScalarState.h>
#include <quant/units/Scalar.h>
#include <quant/units/time/constants.h>
#include <quant/units/time/forward_declarations.h>

#include <cstdint>
#include <iomanip>
#include <ostream>
#include <string>

namespace quant::units::time
{

    /**
     * @brief Represents a time point.
     */
    class TimePoint : public geometry::ScalarState<TimePoint, std::int64_t>
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
         *
         * @return True if time point is zero, false otherwise.
         */
        bool
        is_zero() const
        {
            return _representation == 0;
        }

        std::string
        to_string() const
        {
            for (auto& fn : {&TimePoint::to_days,
                             &TimePoint::to_hours,
                             &TimePoint::to_minutes,
                             &TimePoint::to_seconds,
                             &TimePoint::to_milliseconds})
            {
                Scalar s = (this->*fn)();
                if (s.value > 1)
                {
                    return s.to_string();
                }
            }

            return to_microseconds().to_string();
        }

        /**
         * @brief String representation of the current time point according to given format string.
         *
         * The format is according to https://en.cppreference.com/w/cpp/chrono/c/strftime. For
         * remainder milliseconds or remainder microseconds, special specifiers "%%msec" and
         * "%%usec" were added respectively.
         *
         * Examples using "%M", "%S", "%%msec", "%%usec" - note that the trailing "m" and "s" are to
         * designate unit in the output:
         * - `to_string("%Mm %Ss")`        = `"10m 10s"`
         * - `to_string("%Mm %S.%%msecs")` = `"10m 10.987s"`
         * - `to_string("%Mm %S.%%usecs")` = `"10m 10.986789s"`
         *
         * @param format Format string.
         * @return Formatted time point.
         */
        std::string
        to_string(std::string const& format) const;

    protected:
        using geometry::ScalarState<TimePoint, std::int64_t>::ScalarState;
    };

    inline std::ostream&
    operator<<(std::ostream& out, TimePoint const& rhs)
    {
        return out << rhs.to_string();
    }

}  // namespace quant::units::time
