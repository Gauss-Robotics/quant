#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/framed_units/position/forward_declarations.h>
#include <quant/units/position/SpatialDisplacement.h>

namespace quant::framed_units::position
{

    class SpatialDisplacement : public Framed<units::position::SpatialDisplacement>
    {
    public:
        using Framed<units::position::SpatialDisplacement>::Framed;
    };

    inline std::ostream&
    operator<<(std::ostream& os, framed_units::position::SpatialDisplacement const& rhs)
    {
        return os << rhs.to_string();
    }

}  // namespace quant::framed_units::position
