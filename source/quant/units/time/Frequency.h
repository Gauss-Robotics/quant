#pragma once

#include <quant/units/time/Duration.h>

#include <cstdint>
#include <ostream>
#include <string>

namespace quant::units::time
{

    /**
     * @brief Represents a frequency.
     */
    class Frequency
    {
        // Public API.
    public:
        Frequency(Duration const& cycleDuration);

        static Frequency
        hertz(std::int64_t hertz);

        static Frequency
        hertzDouble(double hertz);

        std::int64_t
        toHertz() const;

        double
        toHertzDouble() const;

        Duration
        toCycleDuration() const;

        std::string
        toFrequencyString() const;

        // Operators.
    public:
        Frequency
        operator+(Frequency const& rhs) const;

        Frequency&
        operator+=(Frequency const& rhs);

        Frequency
        operator-(Frequency const& rhs) const;

        Frequency&
        operator-=(Frequency const& rhs);

        Frequency
        operator*(double rhs) const;

        Frequency
        operator*(int rhs) const;

        Frequency
        operator*(std::int64_t rhs) const;

        Frequency&
        operator*=(double rhs);

        Frequency&
        operator*=(int rhs);

        Frequency&
        operator*=(std::int64_t rhs);

        double
        operator/(Frequency const& rhs) const;

        Frequency
        operator/(double rhs) const;

        Frequency
        operator/(int rhs) const;

        Frequency
        operator/(std::int64_t rhs) const;

        Frequency&
        operator/=(double rhs);

        Frequency&
        operator/=(int rhs);

        Frequency&
        operator/=(std::int64_t rhs);

        bool
        operator<(Frequency const& rhs) const;

        bool
        operator<=(Frequency const& rhs) const;

        bool
        operator==(Frequency const& rhs) const;

        bool
        operator!=(Frequency const& rhs) const;

        bool
        operator>=(Frequency const& rhs) const;

        bool
        operator>(Frequency const& rhs) const;

    protected:
        /**
         * @brief Current cycle duration.
         */
        Duration cycleDuration_;
    };

    Frequency
    operator/(double cyclesPerDuration, Duration const& duration);

    Frequency
    operator/(int cyclesPerDuration, Duration const& duration);

    Frequency
    operator/(std::int64_t cyclesPerDuration, Duration const& duration);

    std::ostream&
    operator<<(std::ostream& out, Frequency const& rhs);

}  // namespace quant::units::time
