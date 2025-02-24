#include "TwistDifference.h"

namespace quant::units::velocity
{
    TwistDifference::TwistDifference(LinearVelocityDifference const& linear,
                                     AngularVelocityDifference const& angular) :
        Difference(Twist(static_cast<LinearVelocity const>(linear),
                         static_cast<AngularVelocity const>(angular)))
    {
    }

    LinearVelocityDifference
    TwistDifference::linear() const
    {
        return LinearVelocityDifference{_difference_object.linear()};
    }

    AngularVelocityDifference
    TwistDifference::angular() const
    {
        return AngularVelocityDifference{_difference_object.angular()};
    }

    std::ostream&
    operator<<(std::ostream& os, TwistDifference const& rhs)
    {
        return os << rhs.to_string();
    }
}  // namespace quant::units::velocity