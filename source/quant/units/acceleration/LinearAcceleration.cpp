#include "LinearAcceleration.h"

namespace quant::units::acceleration
{

    LinearAcceleration
    LinearAcceleration::millimeters_per_second_squared(geometry::Vector const& xyz)
    {
        return {xyz * constants::mmpss2mpss};
    }

    LinearAcceleration
    LinearAcceleration::meters_per_second_squared(geometry::Vector const& xyz)
    {
        return {xyz};
    }

    Vector
    LinearAcceleration::to_millimeters_per_second_squared() const
    {
        return {to_vector() * constants::mpss2mmpss,
                constants::names::linear_acceleration,
                constants::symbols::meters_per_second_squared};
    }

    Vector
    LinearAcceleration::to_meters_per_second_squared() const
    {
        return {to_vector(),
                constants::names::linear_acceleration,
                constants::symbols::meters_per_second_squared};
    }

    std::string
    LinearAcceleration::to_string() const
    {
        return to_millimeters_per_second_squared().to_string();
    }

    std::ostream&
    operator<<(std::ostream& os, LinearAcceleration const& rhs)
    {
        return os << rhs.to_millimeters_per_second_squared();
    }
}  // namespace quant::units::acceleration
