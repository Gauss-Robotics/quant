#include "AngularJerk.h"


namespace simox::core::units::jerk
{

} // namespace simox::core::units::jerk


namespace simox::core::units
{

    std::ostream&
    jerk::operator<<(std::ostream& out, const AngularJerk& rhs)
    {
        out << rhs.toString();
        return out;
    }

} // namespace simox::core::units
