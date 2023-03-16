#include "AngularVelocity.h"


namespace simox::core::units::velocity
{

} // namespace simox::core::units::velocity


namespace simox::core::units
{

    std::ostream&
    velocity::operator<<(std::ostream& out, const AngularVelocity& rhs)
    {
        out << rhs.toString();
        return out;
    }

} // namespace simox::core::units
