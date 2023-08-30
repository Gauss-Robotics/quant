#include "DateTime.h"

/*
#include <quant/core/clock/Clock.h>

#include <quantUtility/algorithm/string/string_tools.h>

#include <iomanip>
#include <sstream>


namespace quant::time
{

    const Duration DateTime::invalidTimeSinceEpoch_ =
        Duration::MicroSeconds(std::numeric_limits<std::int64_t>::min());


    DateTime::DateTime() : timeSinceEpoch_{}, clockType_{ClockType::Unknown}, hostname_{"unknown"}
    {
        ;
    }


    DateTime::DateTime(Duration timeSinceEpoch, ClockType clock, const std::string& hostname) :
        timeSinceEpoch_{timeSinceEpoch}, clockType_{clock}, hostname_{hostname}
    {
        ;
    }


    DateTime::DateTime(std::int64_t microSecondsSinceEpoch,
                       ClockType clock,
                       const std::string& hostname) :
        timeSinceEpoch_{TimePoint::MicroSeconds(microSecondsSinceEpoch)},
        clockType_{clock},
        hostname_{hostname}
    {
        ;
    }


    DateTime
    DateTime::Now()
    {
        return DefaultClock.now();
    }


    DateTime
    DateTime::Invalid()
    {
        return DateTime(invalidTimeSinceEpoch_);
    }


    std::string
    DateTime::toDateString() const
    {
        return toString("%Y-%m-%d");
    }


    std::string
    DateTime::toTimeString() const
    {
        return toString("%H-%M-%S.%%usec");
    }


    std::string
    DateTime::toDateTimeString() const
    {
        return toDateString() + "_" + toTimeString();
    }


    std::string
    DateTime::toString(const std::string& format) const
    {
        return timeSinceEpoch_.toDurationString(format);
    }


    std::int64_t
    DateTime::toMicroSecondsSinceEpoch() const
    {
        return timeSinceEpoch_.toMicroSeconds();
    }


    std::int64_t
    DateTime::toMilliSecondsSinceEpoch() const
    {
        return timeSinceEpoch_.toMilliSeconds();
    }


    std::int64_t
    DateTime::toSecondsSinceEpoch() const
    {
        return timeSinceEpoch_.toSeconds();
    }


    Duration
    DateTime::toDurationSinceEpoch() const
    {
        return timeSinceEpoch_;
    }


    ClockType
    DateTime::clockType() const
    {
        return clockType_;
    }


    std::string
    DateTime::hostname() const
    {
        return hostname_;
    }

    bool
    DateTime::isValid() const
    {
        return timeSinceEpoch_ != invalidTimeSinceEpoch_;
    }

    bool
    DateTime::isInvalid() const
    {
        return not isValid();
    }


    DateTime
    DateTime::operator+(const Duration& rhs) const
    {
        return DateTime(timeSinceEpoch_ + rhs, clockType_, hostname_);
    }


    DateTime&
    DateTime::operator+=(const Duration& rhs)
    {
        timeSinceEpoch_ += rhs;
        return *this;
    }


    DateTime
    DateTime::operator-(const Duration& rhs) const
    {
        return DateTime(timeSinceEpoch_ - rhs, clockType_, hostname_);
    }


    DateTime&
    DateTime::operator-=(const Duration& rhs)
    {
        timeSinceEpoch_ -= rhs;
        return *this;
    }


    Duration
    DateTime::operator-(const DateTime& rhs) const
    {
        return timeSinceEpoch_ - rhs.toDurationSinceEpoch();
    }


    bool
    DateTime::operator<(const DateTime& rhs) const
    {
        return timeSinceEpoch_ < rhs.toDurationSinceEpoch();
    }


    bool
    DateTime::operator<=(const DateTime& rhs) const
    {
        return timeSinceEpoch_ <= rhs.toDurationSinceEpoch();
    }


    bool
    DateTime::operator==(const DateTime& rhs) const
    {
        return timeSinceEpoch_ == rhs.toDurationSinceEpoch();
    }


    bool
    DateTime::operator>(const DateTime& rhs) const
    {
        return timeSinceEpoch_ > rhs.toDurationSinceEpoch();
    }


    bool
    DateTime::operator>=(const DateTime& rhs) const
    {
        return timeSinceEpoch_ >= rhs.toDurationSinceEpoch();
    }


    bool
    DateTime::operator!=(const DateTime& rhs) const
    {
        return timeSinceEpoch_ != rhs.toDurationSinceEpoch();
    }


    std::ostream&
    operator<<(std::ostream& out, const DateTime& rhs)
    {
        out << rhs.toDateTimeString();
        return out;
    }

} // namespace quant::time
*/
