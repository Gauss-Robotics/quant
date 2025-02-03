#include "LinearAcceleration.h"

namespace quant::units::acceleration
{

    LinearAcceleration
    LinearAcceleration::millimeters_per_second_squared(geometry::Vector const& xyz)
    {
        return {xyz};
    }

    LinearAcceleration
    LinearAcceleration::millimeters_per_second_squared(Eigen::Vector3d const& xyz)
    {
        return {xyz};
    }

    LinearAcceleration
    LinearAcceleration::meters_per_second_squared(geometry::Vector const& xyz)
    {
        return {xyz * constants::mpss2mmpss};
    }

    LinearAcceleration
    LinearAcceleration::meters_per_second_squared(Eigen::Vector3d const& xyz)
    {
        return {xyz * constants::mpss2mmpss};
    }

    Vector
    LinearAcceleration::to_millimeters_per_second_squared() const
    {
        return {to_vector(),
                constants::names::linear_acceleration,
                constants::symbols::meters_per_second_squared};
    }

    Vector
    LinearAcceleration::to_meters_per_second_squared() const
    {
        return {to_vector() * constants::mmpss2mpss,
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
