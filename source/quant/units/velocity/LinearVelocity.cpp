#include "LinearVelocity.h"

#include <quant/units/position/LinearDisplacement.h>

namespace quant::units::velocity
{

    LinearVelocity
    LinearVelocity::millimeters_per_second(geometry::Vector xyz)
    {
        return {xyz};
    }

    LinearVelocity
    LinearVelocity::meters_per_second(geometry::Vector xyz)
    {
        return {xyz * constants::mps2mmps};
    }

    Vector
    LinearVelocity::to_millimeters_per_second() const
    {
        return {to_vector(),
                constants::names::linear_velocity,
                constants::symbols::millimeters_per_second};
    }

    Vector
    LinearVelocity::to_meters_per_second() const
    {
        return {to_vector() * constants::mmps2mps,
                constants::names::linear_velocity,
                constants::symbols::meters_per_second};
    }

    Speed
    LinearVelocity::to_speed() const
    {
        return Speed::millimeters_per_second(_representation.norm());
    }

    std::string
    LinearVelocity::to_string() const
    {
        for (auto fn : {&LinearVelocity::to_meters_per_second})
        {
            Vector v = (this->*fn)();
            if (v.x > 1 or v.y > 1 or v.z > 1)
            {
                return v.to_string();
            }
        }

        return to_millimeters_per_second().to_string();
    }

    std::ostream&
    operator<<(std::ostream& os, LinearVelocity const& rhs)
    {
        return os << rhs.to_string();
    }
}  // namespace quant::units::velocity

namespace quant
{

    LinearVelocity
    operator/(LinearDisplacement const& dx, Duration const& dt)
    {
        return LinearVelocity::millimeters_per_second(dx.to_millimeters() / dt.to_seconds());
    }

}  // namespace quant
