#include "LinearVelocity.h"


namespace simox::core::units::velocity
{

} // namespace simox::core::units::velocity


namespace simox::core::units
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
        const std::string unit = "mm/s";
        out << rhs.toString(unit);
        return out;
    }

} // namespace simox::core::units
