#include "Torque.h"

namespace quant::units::force
{
    Torque
    Torque::newton_meters(geometry::AxisAngle aa)
    {
        return {aa};
    }

    Torque
    Torque::newton_meters(geometry::Vector vector)
    {
        return {vector.to_eigen()};
    }

    AxisAngle
    Torque::to_newton_meters() const
    {
        return {to_axis_angle(), constants::names::torque, constants::symbols::newton_meters};
    }

    std::string
    Torque::to_string() const
    {
        return to_newton_meters().to_string();
    }

    std::ostream&
    operator<<(std::ostream& out, Torque const& rhs)
    {
        return out << rhs.to_newton_meters();
    }
}  // namespace quant::units::force