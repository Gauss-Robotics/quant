#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/position/Pose.h>
#include <quant/units/position/LinearDisplacement.h>
#include <quant/units/position/AngularDisplacement.h>
#include <quant/units/position/forward_declarations.h>

namespace quant::units::position
{

    class SpatialDisplacement : public geometry::Difference<Pose>
    {

    public:
        using Difference::Difference;
        SpatialDisplacement(LinearDisplacement const& linear, AngularDisplacement const& angular);

        LinearDisplacement
        linear() const;

        AngularDisplacement
        angular() const;
    };

    inline std::ostream&
    operator<<(std::ostream& os, SpatialDisplacement const& rhs)
    {
        return os << rhs.to_string();
    }

}  // namespace quant::units::position
