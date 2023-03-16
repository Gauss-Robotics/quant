#pragma once


#include <cstdint>
#include <ostream>
#include <string>

#include <simox/core/units/time/Duration.h>


namespace simox::core::units::time
{

    /**
     * @brief Represents a frequency.
     */
    class Frequency
    {
        // Public API.
    public:
        Frequency(const Duration& cycleDuration);

        static Frequency Hertz(std::int64_t hertz);

        static Frequency HertzDouble(double hertz);

        std::int64_t toHertz() const;

        double toHertzDouble() const;

        Duration toCycleDuration() const;

        std::string toFrequencyString() const;

        // Operators.
    public:
        Frequency operator+(const Frequency& rhs) const;

        Frequency& operator+=(const Frequency& rhs);

        Frequency operator-(const Frequency& rhs) const;

        Frequency& operator-=(const Frequency& rhs);

        Frequency operator*(double rhs) const;

        Frequency operator*(int rhs) const;

        Frequency operator*(std::int64_t rhs) const;

        Frequency& operator*=(double rhs);

        Frequency& operator*=(int rhs);

        Frequency& operator*=(std::int64_t rhs);

        double operator/(const Frequency& rhs) const;

        Frequency operator/(double rhs) const;

        Frequency operator/(int rhs) const;

        Frequency operator/(std::int64_t rhs) const;

        Frequency& operator/=(double rhs);

        Frequency& operator/=(int rhs);

        Frequency& operator/=(std::int64_t rhs);

        bool operator<(const Frequency& rhs) const;

        bool operator<=(const Frequency& rhs) const;

        bool operator==(const Frequency& rhs) const;

        bool operator!=(const Frequency& rhs) const;

        bool operator>=(const Frequency& rhs) const;

        bool operator>(const Frequency& rhs) const;

    protected:
        /**
         * @brief Current cycle duration.
         */
        Duration cycleDuration_;
    };


    Frequency operator/(double cyclesPerDuration, const Duration& duration);

    Frequency operator/(int cyclesPerDuration, const Duration& duration);

    Frequency operator/(std::int64_t cyclesPerDuration, const Duration& duration);


    std::ostream& operator<<(std::ostream& out, const Frequency& rhs);

} // namespace simox::core::units::time


namespace simox
{
    using core::units::time::Frequency;
} // namespace simox
