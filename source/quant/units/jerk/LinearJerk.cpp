#include "LinearJerk.h"


namespace simox::core::units::jerk
{

} // namespace simox::core::units::jerk


namespace simox::core::units
{

    std::ostream&
    jerk::operator<<(std::ostream& out, const LinearJerk& rhs)
    {
        out << rhs.toString();
        return out;
    }

} // namespace simox::core::units
