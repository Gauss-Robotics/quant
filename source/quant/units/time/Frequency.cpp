#include "Frequency.h"

#include <iomanip>
#include <limits>
#include <sstream>

#include <quantUtility/algorithm/string/string_tools.h>


namespace quant::units::time
{

    Frequency::Frequency(const Duration& cycleDuration) : cycleDuration_{cycleDuration}
    {
        ;
    }


    Frequency
    Frequency::Hertz(const std::int64_t hertz)
    {
        if (hertz == 0)
        {
            Duration d = Duration::MicroSeconds(std::numeric_limits<std::int64_t>::max());
            return {d};
        }
        return {Duration::Seconds(1) / hertz};
    }


    Frequency
    Frequency::HertzDouble(const double hertz)
    {
        if (hertz == 0)
        {
            return {Duration::MicroSeconds(std::numeric_limits<std::int64_t>::max())};
        }
        return {Duration::Seconds(1) / hertz};
    }


    std::int64_t
    Frequency::toHertz() const
    {
        if (cycleDuration_.pointFromOrigin().isZero())
        {
            return std::numeric_limits<std::int64_t>::max();
        }
        return static_cast<std::int64_t>(toHertzDouble() + 0.5);
    }


    double
    Frequency::toHertzDouble() const
    {
        if (cycleDuration_.pointFromOrigin().isZero())
        {
            return std::numeric_limits<double>::infinity();
        }
        return 1 / cycleDuration_.pointFromOrigin().toSecondsDouble();
    }


    Duration
    Frequency::toCycleDuration() const
    {
        return cycleDuration_;
    }


    std::string
    Frequency::toFrequencyString() const
    {
        if (cycleDuration_.pointFromOrigin().isZero())
        {
            return "infinite Hz";
        }

        return std::to_string(toHertz()) + "Hz";
    }


    Frequency
    Frequency::operator+(const Frequency& rhs) const
    {
        return Frequency::Hertz(toHertzDouble() + rhs.toHertzDouble());
    }


    Frequency&
    Frequency::operator+=(const Frequency& rhs)
    {
        cycleDuration_ = Frequency::Hertz(toHertzDouble() + rhs.toHertzDouble()).toCycleDuration();
        return *this;
    }


    Frequency
    Frequency::operator-(const Frequency& rhs) const
    {
        return Frequency::Hertz(toHertzDouble() - rhs.toHertzDouble());
    }


    Frequency&
    Frequency::operator-=(const Frequency& rhs)
    {
        cycleDuration_ = Frequency::Hertz(toHertzDouble() - rhs.toHertzDouble()).toCycleDuration();
        return *this;
    }


    Frequency
    Frequency::operator*(double rhs) const
    {
        return {cycleDuration_ / rhs};
    }


    Frequency
    Frequency::operator*(int rhs) const
    {
        return {cycleDuration_ / rhs};
    }


    Frequency
    Frequency::operator*(std::int64_t rhs) const
    {
        return {cycleDuration_ / rhs};
    }


    Frequency&
    Frequency::operator*=(double rhs)
    {
        cycleDuration_ /= rhs;
        return *this;
    }


    Frequency&
    Frequency::operator*=(int rhs)
    {
        cycleDuration_ /= rhs;
        return *this;
    }


    Frequency&
    Frequency::operator*=(std::int64_t rhs)
    {
        cycleDuration_ /= rhs;
        return *this;
    }


    double
    Frequency::operator/(const Frequency& rhs) const
    {
        return toHertzDouble() / rhs.toHertzDouble();
    }


    Frequency
    Frequency::operator/(double rhs) const
    {
        return Frequency(cycleDuration_ * rhs);
    }


    Frequency
    Frequency::operator/(int rhs) const
    {
        return Frequency(cycleDuration_ * rhs);
    }


    Frequency
    Frequency::operator/(std::int64_t rhs) const
    {
        return Frequency(cycleDuration_ * rhs);
    }


    Frequency&
    Frequency::operator/=(double rhs)
    {
        cycleDuration_ *= rhs;
        return *this;
    }


    Frequency&
    Frequency::operator/=(int rhs)
    {
        cycleDuration_ *= rhs;
        return *this;
    }


    Frequency&
    Frequency::operator/=(std::int64_t rhs)
    {
        cycleDuration_ *= rhs;
        return *this;
    }


    bool
    Frequency::operator<(const Frequency& rhs) const
    {
        return cycleDuration_ > rhs.cycleDuration_;
    }


    bool
    Frequency::operator<=(const Frequency& rhs) const
    {
        return cycleDuration_ >= rhs.cycleDuration_;
    }


    bool
    Frequency::operator==(const Frequency& rhs) const
    {
        return cycleDuration_ == rhs.cycleDuration_;
    }


    bool
    Frequency::operator!=(const Frequency& rhs) const
    {
        return cycleDuration_ != rhs.cycleDuration_;
    }


    bool
    Frequency::operator>=(const Frequency& rhs) const
    {
        return cycleDuration_ <= rhs.cycleDuration_;
    }


    bool
    Frequency::operator>(const Frequency& rhs) const
    {
        return cycleDuration_ < rhs.cycleDuration_;
    }


    Frequency
    operator/(const double cyclesPerDuration, const Duration& duration)
    {
        const double cyclesPerSecond = cyclesPerDuration / duration.toSecondsDouble();
        return {Duration::Seconds(1) / cyclesPerSecond};
    }


    Frequency
    operator/(const int cyclesPerDuration, const Duration& duration)
    {
        return static_cast<double>(cyclesPerDuration) / duration;
    }


    Frequency
    operator/(const std::int64_t cyclesPerDuration, const Duration& duration)
    {
        return static_cast<double>(cyclesPerDuration) / duration;
    }


    std::ostream&
    operator<<(std::ostream& out, const Frequency& rhs)
    {
        out << rhs.toFrequencyString();
        return out;
    }

} // namespace quant::units::time
