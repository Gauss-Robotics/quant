#pragma once

#include <quant/geometry_fwd.h>

namespace quant::units::mass
{

    class Mass;

    struct Domain
    {
        using State = Mass;
    };

}  // namespace quant::units::mass

namespace quant
{

    using units::mass::Mass;

}  // namespace quant
