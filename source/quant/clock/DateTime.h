#pragma once


#include <cstdint>
#include <ostream>
#include <string>

#include <quant/core/clock/ClockType.h>
#include <quant/core/units/time/Duration.h>


namespace quant::time
{

    /**
     * @brief Represents a point in time.
     *
     * API and implementation to match IceUtil::Time (where applicable).
     */
    class DateTime
    {

    public:
        DateTime();

        DateTime(Duration timeSinceEpoch,
                 ClockType clock = ClockType::Virtual,
                 const std::string& hostname = "unknown");

        DateTime(std::int64_t microSecondsSinceEpoch,
                 ClockType clock = ClockType::Virtual,
                 const std::string& hostname = "unknown");

        static DateTime Now();
        static DateTime Invalid();

        std::string toDateString() const;

        std::string toTimeString() const;

        std::string toDateTimeString() const;

        /**
         * @brief String representation of current date time according to given format string.
         *
         * The format is according to https://en.cppreference.com/w/cpp/chrono/c/strftime. For
         * milli seconds and micro seconds, special specifiers "%%msec" and "%%usec" were added
         * respectively.
         *
         * Example format string for "2022-03-04_16-59-10.981789": "%Y-%m-%d_%H-%M-%S.%%usec".
         *
         * @param format Format string.
         * @return Formatted date time.
         */
        std::string toString(const std::string& format) const;

        std::int64_t toMicroSecondsSinceEpoch() const;

        std::int64_t toMilliSecondsSinceEpoch() const;

        std::int64_t toSecondsSinceEpoch() const;

        Duration toDurationSinceEpoch() const;

        ClockType clockType() const;

        std::string hostname() const;

        bool isValid() const;
        bool isInvalid() const;

        // Operators.
    public:
        DateTime operator+(const Duration& rhs) const;

        DateTime& operator+=(const Duration& rhs);

        DateTime operator-(const Duration& rhs) const;

        DateTime& operator-=(const Duration& rhs);

        Duration operator-(const DateTime& rhs) const;

        bool operator<(const DateTime& rhs) const;

        bool operator<=(const DateTime& rhs) const;

        bool operator==(const DateTime& rhs) const;

        bool operator>(const DateTime& rhs) const;

        bool operator>=(const DateTime& rhs) const;

        bool operator!=(const DateTime& rhs) const;

    private:
        static const Duration invalidTimeSinceEpoch_;

        Duration timeSinceEpoch_;

        ClockType clockType_;

        std::string hostname_;
    };


    std::ostream& operator<<(std::ostream& out, const DateTime& rhs);

} // namespace quant::time


namespace quant
{
    using core::time::DateTime;
} // namespace quant
