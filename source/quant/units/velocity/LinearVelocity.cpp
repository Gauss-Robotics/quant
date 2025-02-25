#include "LinearVelocity.h"

#include <quant/geometry/Vector.h>
#include <quant/units/position/LinearDisplacement.h>
#include <quant/units/position/forward_declarations.h>
#include <quant/units/time/Duration.h>
#include <quant/units/time/forward_declarations.h>

#include <cstdlib>

#include "constants.h"
#include "forward_declarations.h"

namespace quant::units::velocity
{

    LinearVelocity
    LinearVelocity::millimeters_per_second(geometry::Vector xyz)
    {
        return {xyz * constants::mmps2mps};
    }

    LinearVelocity
    LinearVelocity::meters_per_second(geometry::Vector xyz)
    {
        return {xyz};
    }

    Vector
    LinearVelocity::to_millimeters_per_second() const
    {
        return {to_vector() * constants::mps2mmps,
                constants::names::linear_velocity,
                constants::symbols::millimeters_per_second};
    }

    Vector
    LinearVelocity::to_meters_per_second() const
    {
        return {to_vector(),
                constants::names::linear_velocity,
                constants::symbols::meters_per_second};
    }

    Speed
    LinearVelocity::to_speed() const
    {
        return Speed::meters_per_second(_representation.norm());
    }

    std::string
    LinearVelocity::to_string() const
    {
        for (auto fn : {&LinearVelocity::to_meters_per_second})
        {
            Vector v = (this->*fn)();
            if (abs(v.x) > 1 or abs(v.y) > 1 or abs(v.z) > 1)
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
