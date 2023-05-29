#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/position/Pose.h>
#include <quant/units/position_fwd.h>

namespace quant::units::position
{

    class SpatialDisplacement : public geometry::Difference<Pose>
    {

    public:
        using geometry::Difference<Pose>::Difference;
    };

    inline std::ostream&
    operator<<(std::ostream& os, SpatialDisplacement const& rhs)
    {
        return os << rhs.to_string();
    }

}  // namespace quant::units::position
