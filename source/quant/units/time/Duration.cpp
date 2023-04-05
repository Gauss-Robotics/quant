#include "Duration.h"

namespace quant::units::time
{

    bool
    Duration::is_positive() const
    {
        return difference_object_.is_positive();
    }

    bool
    Duration::is_zero() const
    {
        return difference_object_.is_zero();
    }

    Duration
    Duration::operator+(Duration const& rhs) const
    {
        return Duration{TimePoint(this->difference_object_.representation_ +
                                  rhs.difference_object_.representation_)};
    }

    Duration&
    Duration::operator+=(Duration const& rhs)
    {
        this->difference_object_.representation_ += rhs.difference_object_.representation_;
        return *this;
    }

    Duration&
    Duration::operator-=(Duration const& rhs)
    {
        this->difference_object_.representation_ -= rhs.difference_object_.representation_;
        return *this;
    }

    Duration
    Duration::operator*(double rhs) const
    {
        return Duration{TimePoint(this->difference_object_.representation_ * rhs)};
    }

    Duration
    Duration::operator*(int rhs) const
    {
        return Duration{TimePoint(this->difference_object_.representation_ * rhs)};
    }

    Duration&
    Duration::operator*=(double rhs)
    {
        this->difference_object_.representation_ *= rhs;
        return *this;
    }

    Duration&
    Duration::operator*=(int rhs)
    {
        this->difference_object_.representation_ *= rhs;
        return *this;
    }

    double
    Duration::operator/(Duration const& rhs) const
    {
        return difference_object_.to_microseconds() / rhs.difference_object_.to_microseconds();
    }

    Duration
    Duration::operator/(double rhs) const
    {
        return Duration{TimePoint(difference_object_.to_microseconds() / rhs)};
    }

    Duration
    Duration::operator/(int rhs) const
    {
        return Duration{TimePoint(difference_object_.to_microseconds() / rhs)};
    }

    Duration&
    Duration::operator/=(double rhs)
    {
        difference_object_.representation_ /= rhs;
        return *this;
    }

    Duration&
    Duration::operator/=(int rhs)
    {
        difference_object_.representation_ /= rhs;
        return *this;
    }

    bool
    Duration::operator<(Duration const& rhs) const
    {
        return difference_object_ < rhs.difference_object_;
    }

    bool
    Duration::operator<=(Duration const& rhs) const
    {
        return difference_object_ <= rhs.difference_object_;
    }

    bool
    Duration::operator==(Duration const& rhs) const
    {
        return difference_object_ == rhs.difference_object_;
    }

    bool
    Duration::operator!=(Duration const& rhs) const
    {
        return difference_object_ != rhs.difference_object_;
    }

    bool
    Duration::operator>=(Duration const& rhs) const
    {
        return difference_object_ >= rhs.difference_object_;
    }

    bool
    Duration::operator>(Duration const& rhs) const
    {
        return difference_object_ > rhs.difference_object_;
    }

    std::ostream&
    operator<<(std::ostream& out, Duration const& rhs)
    {
        return out << rhs.to_duration_string();
    }

}  // namespace quant::units::time
