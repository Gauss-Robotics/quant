#include "Orientation.h"


namespace quant::units::position
{

} // namespace quant::units::position


namespace quant::units
{

    std::ostream&
    position::operator<<(std::ostream& out, const Orientation& rhs)
    {
        out << rhs.toString("Orientation", "rad");
        return out;
    }

} // namespace quant::units
