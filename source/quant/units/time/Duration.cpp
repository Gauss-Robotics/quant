#include "Duration.h"

namespace quant::units::time
{

    bool
    Duration::isPositive() const
    {
        return differenceObject_.isPositive();
    }

    bool
    Duration::isZero() const
    {
        return differenceObject_.isZero();
    }

    Duration
    Duration::operator+(Duration const& rhs) const
    {
        return Duration{TimePoint(this->differenceObject_.representation_ +
                                  rhs.differenceObject_.representation_)};
    }

    Duration&
    Duration::operator+=(Duration const& rhs)
    {
        this->differenceObject_.representation_ += rhs.differenceObject_.representation_;
        return *this;
    }

    /*Duration
    Duration::operator-(const Duration& rhs) const
    {
        return TimePoint(this->differenceObject_.representation_ -
                         rhs.differenceObject_.representation_)
            .deltaToOrigin();
    }*/

    Duration&
    Duration::operator-=(Duration const& rhs)
    {
        this->differenceObject_.representation_ -= rhs.differenceObject_.representation_;
        return *this;
    }

    Duration
    Duration::operator*(double rhs) const
    {
        return Duration{TimePoint(this->differenceObject_.representation_ * rhs)};
    }

    Duration
    Duration::operator*(int rhs) const
    {
        return Duration{TimePoint(this->differenceObject_.representation_ * rhs)};
    }

    Duration
    Duration::operator*(std::int64_t rhs) const
    {
        return Duration{TimePoint(this->differenceObject_.representation_ * rhs)};
    }

    Duration&
    Duration::operator*=(double rhs)
    {
        this->differenceObject_.representation_ *= rhs;
        return *this;
    }

    Duration&
    Duration::operator*=(int rhs)
    {
        this->differenceObject_.representation_ *= rhs;
        return *this;
    }

    Duration&
    Duration::operator*=(std::int64_t rhs)
    {
        this->differenceObject_.representation_ *= rhs;
        return *this;
    }

    double
    Duration::operator/(Duration const& rhs) const
    {
        return differenceObject_.toMicroSecondsDouble() /
               rhs.differenceObject_.toMicroSecondsDouble();
    }

    Duration
    Duration::operator/(double rhs) const
    {
        return Duration{TimePoint(differenceObject_.toMicroSecondsDouble() / rhs)};
    }

    Duration
    Duration::operator/(int rhs) const
    {
        return Duration{TimePoint(differenceObject_.toMicroSecondsDouble() / rhs)};
    }

    Duration
    Duration::operator/(std::int64_t rhs) const
    {
        return Duration{TimePoint(differenceObject_.toMicroSecondsDouble() / rhs)};
    }

    Duration&
    Duration::operator/=(double rhs)
    {
        differenceObject_.representation_ /= rhs;
        return *this;
    }

    Duration&
    Duration::operator/=(int rhs)
    {
        differenceObject_.representation_ /= rhs;
        return *this;
    }

    Duration&
    Duration::operator/=(std::int64_t rhs)
    {
        differenceObject_.representation_ /= rhs;
        return *this;
    }

    bool
    Duration::operator<(Duration const& rhs) const
    {
        return differenceObject_ < rhs.differenceObject_;
    }

    bool
    Duration::operator<=(Duration const& rhs) const
    {
        return differenceObject_ <= rhs.differenceObject_;
    }

    bool
    Duration::operator==(Duration const& rhs) const
    {
        return differenceObject_ == rhs.differenceObject_;
    }

    bool
    Duration::operator!=(Duration const& rhs) const
    {
        return differenceObject_ != rhs.differenceObject_;
    }

    bool
    Duration::operator>=(Duration const& rhs) const
    {
        return differenceObject_ >= rhs.differenceObject_;
    }

    bool
    Duration::operator>(Duration const& rhs) const
    {
        return differenceObject_ > rhs.differenceObject_;
    }

    std::ostream&
    operator<<(std::ostream& out, Duration const& rhs)
    {
        return out << rhs.toDurationString();
    }

}  // namespace quant::units::time
