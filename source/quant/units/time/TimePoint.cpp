#include "TimePoint.h"

#include <sstream>

namespace quant::units::time
{

    TimePoint
    TimePoint::microSeconds(const std::int64_t microSeconds)
    {
        return {microSeconds};
    }

    std::int64_t
    TimePoint::toMicroSeconds() const
    {
        return representation_;
    }

    bool
    TimePoint::isPositive() const
    {
        return representation_ > 0;
    }

    bool
    TimePoint::isZero() const
    {
        return representation_ == 0;
    }

    bool
    TimePoint::operator<(TimePoint const& rhs) const
    {
        return representation_ < rhs.representation_;
    }

    bool
    TimePoint::operator<=(TimePoint const& rhs) const
    {
        return representation_ <= rhs.representation_;
    }

    bool
    TimePoint::operator==(TimePoint const& rhs) const
    {
        return representation_ == rhs.representation_;
    }

    bool
    TimePoint::operator!=(TimePoint const& rhs) const
    {
        return representation_ != rhs.representation_;
    }

    bool
    TimePoint::operator>=(TimePoint const& rhs) const
    {
        return representation_ >= rhs.representation_;
    }

    bool
    TimePoint::operator>(TimePoint const& rhs) const
    {
        return representation_ > rhs.representation_;
    }

}  // namespace quant::units::time

namespace quant::units
{

    std::ostream&
    time::operator<<(std::ostream& out, TimePoint const& rhs)
    {
        out << rhs.toString("TimePoint", "s");
        return out;
    }

}  // namespace quant::units
