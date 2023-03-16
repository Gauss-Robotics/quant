#include "Force.h"


namespace simox::core::units::force
{

} // namespace simox::core::units::force


namespace simox::core::units
{

    std::ostream&
    force::operator<<(std::ostream& out, const Force& rhs)
    {
        out << rhs.toString();
        return out;
    }

} // namespace simox::core::units
