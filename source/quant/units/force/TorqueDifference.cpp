#include "TorqueDifference.h"

namespace quant::units::force
{
    TorqueDifference
    TorqueDifference::newton_meters(AxisAngle const& aa)
    {
        return TorqueDifference{Torque::newton_meters(aa)};
    }

    std::ostream&
    operator<<(std::ostream& out, TorqueDifference const& rhs)
    {
        return out << rhs.to_string();
    }
}  // namespace quant::units::force