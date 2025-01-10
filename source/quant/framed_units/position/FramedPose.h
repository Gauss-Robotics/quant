#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/framed_units/position/forward_declarations.h>
#include <quant/units/position/Pose.h>
#include <quant/units/position/SpatialDisplacement.h>

#include "forward_declarations.h"

namespace quant::framed_geometry
{
    template <>
    struct FrameConversion<units::position::Pose>
    {
        static units::position::Pose&
        convert(units::position::Pose& pose,
                units::position::SpatialDisplacement const& /*transform*/)
        {
            // TODO: implement
            return pose;
        }
    };
}  // namespace quant::framed_geometry

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
