#include "LinearAcceleration.h"


namespace simox::core::units::acceleration
{

} // namespace simox::core::units::acceleration


namespace simox::core::units
{

    std::ostream&
    acceleration::operator<<(std::ostream& out, const LinearAcceleration& rhs)
    {
        out << rhs.toString();
        return out;
    }

} // namespace simox::core::units
