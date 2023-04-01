#include "TimePoint.h"

#include <sstream>

namespace quant::units::time
{

    TimePoint
    TimePoint::micro_seconds(const std::int64_t micro_seconds)
    {
        return {micro_seconds};
    }

    std::int64_t
    TimePoint::to_micro_seconds() const
    {
        return representation_;
    }

    bool
    TimePoint::is_positive() const
    {
        return representation_ > 0;
    }

    bool
    TimePoint::is_zero() const
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
