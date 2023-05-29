#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/framed_units/position_fwd.h>
#include <quant/units/position/Pose.h>

namespace quant::framed_units::position
{

    class Pose : public Framed<units::position::Pose>
    {
    public:
        using Framed<units::position::Pose>::Framed;
    };

    inline std::ostream&
    operator<<(std::ostream& os, framed_units::position::Pose const& rhs)
    {
        return os << rhs.to_string();
    }

}  // namespace quant::framed_units::position
