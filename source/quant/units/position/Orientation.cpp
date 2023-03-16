#include "Orientation.h"


namespace simox::core::units::position
{

} // namespace simox::core::units::position


namespace simox::core::units
{

    std::ostream&
    position::operator<<(std::ostream& out, const Orientation& rhs)
    {
        out << rhs.toString();
        return out;
    }

} // namespace simox::core::units
