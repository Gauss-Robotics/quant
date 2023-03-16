#include "LinearVelocity.h"


namespace quant::units::velocity
{

} // namespace quant::units::velocity


namespace quant::units
{

    velocity::LinearVelocity
    position::operator/(const Displacement& dx, const Duration& dt)
    {
        const Eigen::Vector3d xyz =
            dx.pointFromOrigin().toMilliMeters().toEigen() / dt.toSecondsDouble();
        return velocity::LinearVelocity::MilliMetersPerSecond(
            {.x = xyz.x(), .y = xyz.y(), .z = xyz.z()});
    }

    std::ostream&
    velocity::operator<<(std::ostream& out, const LinearVelocity& rhs)
    {
        out << rhs.toString("LinearVelocity", "mm/s");
        return out;
    }

} // namespace quant::units
