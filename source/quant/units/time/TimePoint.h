#pragma once

#include <quant/geometry/ScalarQuantity.h>
#include <quant/units/time/detail/UnitConversions.h>
#include <quant/units/time_fwd.h>

#include <cstdint>
#include <ostream>
#include <string>

namespace quant::units::time
{

    /**
     * @brief Represents a time point.
     */
    class TimePoint :
        // A time point is a scalar integer quantity.
        public geometry::ScalarIntegerQuantity<TimePoint, Duration>,
        // A time point can be specified in several temporal units.
        public detail::UnitConversions<TimePoint>
    {
        friend Duration;

        // Construct.
    public:
        /**
         * @brief Constructs a time point in microseconds.
         * @param microSeconds Amount of microseconds.
         * @return TimePoint instance.
         */
        static TimePoint
        MicroSeconds(std::int64_t microSeconds);

        /**
         * @brief Returns the amount of microseconds.
         * @return Amount of microseconds.
         */
        std::int64_t
        toMicroSeconds() const;

        /**
         * @brief Tests whether the time point is positive (value in µs > 0).
         * @return True if time point is positive, else otherwise.
         */
        bool
        isPositive() const;

        /**
         * @brief Tests whether the time point is zero.
         * @return True if time point is zero, else otherwise.
         */
        bool
        isZero() const;

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
        toTimePointString() const
        {
            return toQuantityUnitString();
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
        toTimePointString(std::string const& format) const
        {
            return toQuantityUnitString(format);
        }

        // Operators.

        bool
        operator<(TimePoint const& rhs) const;

        bool
        operator<=(TimePoint const& rhs) const;

        bool
        operator==(TimePoint const& rhs) const;

        bool
        operator!=(TimePoint const& rhs) const;

        bool
        operator>=(TimePoint const& rhs) const;

        bool
        operator>(TimePoint const& rhs) const;

    protected:
        using geometry::ScalarIntegerQuantity<TimePoint, Duration>::ScalarQuantity;
    };

    std::ostream&
    operator<<(std::ostream& out, TimePoint const& rhs);

}  // namespace quant::units::time

namespace quant
{
    using units::time::TimePoint;
}  // namespace quant
