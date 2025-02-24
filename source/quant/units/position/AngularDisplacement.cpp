#include "AngularDisplacement.h"

namespace quant::units::position
{
    AngularDisplacement
    AngularDisplacement::radians(geometry::AxisAngle const& aa)
    {
        return AngularDisplacement{Orientation::radians(aa)};
    }

    AngularDisplacement
    AngularDisplacement::degrees(geometry::AxisAngle const& aa)
    {
        return AngularDisplacement{Orientation::degrees(aa)};
    }

    AngularDisplacement
    AngularDisplacement::radians(Eigen::Quaterniond const& q)
    {
        return AngularDisplacement{Orientation::radians(q)};
    }

    AngularDisplacement
    AngularDisplacement::degrees(Eigen::Quaterniond const& q)
    {
        return AngularDisplacement{Orientation::degrees(q)};
    }

    AxisAngle
    AngularDisplacement::to_radians() const
    {
        return _difference_object.to_radians();
    }

    AxisAngle
    AngularDisplacement::to_degrees() const
    {
        return _difference_object.to_degrees();
    }

    std::ostream&
    operator<<(std::ostream& os, AngularDisplacement const& rhs)
    {
        return os << rhs.to_degrees();
    }
}  // namespace quant::units::position