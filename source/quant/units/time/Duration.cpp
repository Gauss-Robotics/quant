#include "Duration.h"


namespace simox::core::units::time
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
    Duration::operator+(const Duration& rhs) const
    {
        return TimePoint(this->differenceObject_.representation_ +
                         rhs.differenceObject_.representation_)
            .deltaToOrigin();
    }


    Duration&
    Duration::operator+=(const Duration& rhs)
    {
        this->differenceObject_.representation_ += rhs.differenceObject_.representation_;
        return *this;
    }


    Duration
    Duration::operator-(const Duration& rhs) const
    {
        return TimePoint(this->differenceObject_.representation_ -
                         rhs.differenceObject_.representation_)
            .deltaToOrigin();
    }


    Duration&
    Duration::operator-=(const Duration& rhs)
    {
        this->differenceObject_.representation_ -= rhs.differenceObject_.representation_;
        return *this;
    }


    Duration
    Duration::operator*(double rhs) const
    {
        return TimePoint(this->differenceObject_.representation_ * rhs).deltaToOrigin();
    }


    Duration
    Duration::operator*(int rhs) const
    {
        return TimePoint(this->differenceObject_.representation_ * rhs).deltaToOrigin();
    }


    Duration
    Duration::operator*(std::int64_t rhs) const
    {
        return TimePoint(this->differenceObject_.representation_ * rhs).deltaToOrigin();
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
    Duration::operator/(const Duration& rhs) const
    {
        return this->differenceObject_.toMicroSecondsDouble() /
               rhs.differenceObject_.toMicroSecondsDouble();
    }


    Duration
    Duration::operator/(double rhs) const
    {
        return TimePoint(this->differenceObject_.toMicroSecondsDouble() / rhs).deltaToOrigin();
    }


    Duration
    Duration::operator/(int rhs) const
    {
        return TimePoint(this->differenceObject_.toMicroSecondsDouble() / rhs).deltaToOrigin();
    }


    Duration
    Duration::operator/(std::int64_t rhs) const
    {
        return TimePoint(this->differenceObject_.toMicroSecondsDouble() / rhs).deltaToOrigin();
    }


    Duration&
    Duration::operator/=(double rhs)
    {
        this->differenceObject_.representation_ /= rhs;
        return *this;
    }


    Duration&
    Duration::operator/=(int rhs)
    {
        this->differenceObject_.representation_ /= rhs;
        return *this;
    }


    Duration&
    Duration::operator/=(std::int64_t rhs)
    {
        this->differenceObject_.representation_ /= rhs;
        return *this;
    }


    bool
    Duration::operator<(const Duration& rhs) const
    {
        return this->differenceObject_ < rhs.differenceObject_;
    }


    bool
    Duration::operator<=(const Duration& rhs) const
    {
        return this->differenceObject_ <= rhs.differenceObject_;
    }


    bool
    Duration::operator==(const Duration& rhs) const
    {
        return this->differenceObject_ == rhs.differenceObject_;
    }


    bool
    Duration::operator!=(const Duration& rhs) const
    {
        return this->differenceObject_ != rhs.differenceObject_;
    }


    bool
    Duration::operator>=(const Duration& rhs) const
    {
        return this->differenceObject_ >= rhs.differenceObject_;
    }


    bool
    Duration::operator>(const Duration& rhs) const
    {
        return this->differenceObject_ > rhs.differenceObject_;
    }


    std::ostream&
    operator<<(std::ostream& out, const Duration& rhs)
    {
        out << rhs.toDurationString();
        return out;
    }

} // namespace simox::core::units::time
