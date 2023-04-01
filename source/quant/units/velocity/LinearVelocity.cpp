#include "LinearVelocity.h"

namespace quant::units::velocity
{

}  // namespace quant::units::velocity

namespace quant::units
{

    velocity::LinearVelocity
    position::operator/(LinearDisplacement const& dx, Duration const& dt)
    {
        const Eigen::Vector3d xyz = dx.to_milli_meters().to_eigen() / dt.to_seconds_double();
        return velocity::LinearVelocity::milli_meters_per_second(
            {.x = xyz.x(), .y = xyz.y(), .z = xyz.z()});
    }

    std::ostream&
    velocity::operator<<(std::ostream& out, LinearVelocity const& rhs)
    {
        out << rhs.to_string("LinearVelocity", "mm/s");
        return out;
    }

}  // namespace quant::units
