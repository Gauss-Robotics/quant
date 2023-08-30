#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/framed_units/time/forward_declarations.h>
#include <quant/units/time/Duration.h>

namespace quant::framed_units::time
{

    class Duration : public Framed<units::time::Duration>
    {
    public:
        using Framed<units::time::Duration>::Framed;
    };

    inline std::ostream&
    operator<<(std::ostream& os, framed_units::time::Duration const& rhs)
    {
        return os << rhs.to_string();
    }

}  // namespace quant::framed_units::time
