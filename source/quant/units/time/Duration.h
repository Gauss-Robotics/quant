#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/time/TimePoint.h>
#include <quant/units/time/detail/UnitConversions.h>
#include <quant/units/time_fwd.h>

namespace quant::geometry
{

    template <>
    struct DefineDifferenceType<quant::TimePoint>
    {
        using DifferenceType = units::time::Duration;
    };

}  // namespace quant::geometry

namespace quant::units::time
{

    /**
     * @brief Represents a duration.
     */
    class Duration :
        // A duration is the difference of time points.
        public Difference<TimePoint>,
        // A duration can be specified in several temporal units.
        public detail::UnitConversions<Duration>
    {

    public:
        Duration() : Difference<TimePoint>()
        {
            ;
        }

        explicit Duration(TimePoint const& t) : Difference<TimePoint>(t)
        {
            ;
        }

        /**
         * @brief Constructs a time point in microseconds.
         * @param microSeconds Amount of microseconds.
         * @return Duration instance.
         */
        static Duration
        MicroSeconds(std::int64_t microSeconds)
        {
            return TimePoint::MicroSeconds(microSeconds).deltaToOrigin();
        }

        /**
         * @brief Returns the amount of microseconds.
         * @return Amount of microseconds.
         */
        std::int64_t
        toMicroSeconds() const
        {
            return differenceObject_.representation_;
        }

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
         * @brief String representation of the current duration in minimal/default format.
         *
         * The minimal representation is a float representation with max. 3 decimals. The unit will
         * be determined by the highest unit whose value is non-zero. For example, 3 seconds and 500
         * milliseconds => "3.5s".
         *
         * @return Formatted duration.
         */
        std::string
        toDurationString() const
        {
            return toQuantityUnitString();
        }

        /**
         * @brief String representation of the current duration according to given format string.
         *
         * The format is according to https://en.cppreference.com/w/cpp/chrono/c/strftime. For
         * milli seconds and micro seconds, special specifiers "%%msec" and "%%usec" were added
         * respectively.
         *
         * Example format string for "10m 10.987s": "%Mm %S.%%msecs".
         *
         * @param format Format string.
         * @return Formatted duration.
         */
        std::string
        toDurationString(std::string const& format) const
        {
            return toQuantityUnitString(format);
        }

        Duration
        operator+(Duration const& rhs) const;

        Duration&
        operator+=(Duration const& rhs);

        Duration
        operator-(Duration const& rhs) const;

        Duration&
        operator-=(Duration const& rhs);

        Duration
        operator*(double rhs) const;

        Duration
        operator*(int rhs) const;

        Duration
        operator*(std::int64_t rhs) const;

        Duration&
        operator*=(double rhs);

        Duration&
        operator*=(int rhs);

        Duration&
        operator*=(std::int64_t rhs);

        double
        operator/(Duration const& rhs) const;

        Duration
        operator/(double rhs) const;

        Duration
        operator/(int rhs) const;

        Duration
        operator/(std::int64_t rhs) const;

        Duration&
        operator/=(double rhs);

        Duration&
        operator/=(int rhs);

        Duration&
        operator/=(std::int64_t rhs);

        bool
        operator<(Duration const& rhs) const;

        bool
        operator<=(Duration const& rhs) const;

        bool
        operator==(Duration const& rhs) const;

        bool
        operator!=(Duration const& rhs) const;

        bool
        operator>=(Duration const& rhs) const;

        bool
        operator>(Duration const& rhs) const;
    };

    std::ostream&
    operator<<(std::ostream& out, Duration const& rhs);

}  // namespace quant::units::time

namespace quant
{

    using units::time::Duration;

}
