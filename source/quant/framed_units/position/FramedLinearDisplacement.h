#pragma once

#include <quant/units/position/forward_declarations.h>

#include <quant/framed_geometry/Framed.h>
#include <quant/units/position/LinearDisplacement.h>

namespace quant::framed_units::position
{
    class LinearDisplacement : public Framed<units::position::LinearDisplacement>
    {
    public:
        using Framed<units::position::LinearDisplacement>::Framed;
    };

    inline std::ostream&
    operator<<(std::ostream& os, framed_units::position::LinearDisplacement const& rhs)
    {
        return os << rhs.to_string();
    }
}