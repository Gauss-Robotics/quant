#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/framed_units/time/forward_declarations.h>
#include <quant/units/time/Frequency.h>

namespace quant::framed_units::time
{

    class Frequency : public Framed<units::time::Frequency>
    {
    public:
        using Framed<units::time::Frequency>::Framed;
    };

    inline std::ostream&
    operator<<(std::ostream& os, framed_units::time::Frequency const& rhs)
    {
        return os << rhs.to_string();
    }

}  // namespace quant::framed_units::time
