#include "WrenchDifference.h"

#include <quant/units/force/ForceDifference.h>
#include <quant/units/force/TorqueDifference.h>

namespace quant::units::force
{
    WrenchDifference::WrenchDifference(ForceDifference const& force,
                                       TorqueDifference const& torque) :
        Difference{Wrench{static_cast<Force const>(force), static_cast<Torque const>(torque)}}
    {
    }

    std::ostream&
    operator<<(std::ostream& out, WrenchDifference const& rhs)
    {
        return out << rhs.to_string();
    }
}  // namespace quant::units::force