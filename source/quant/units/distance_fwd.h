#pragma once

namespace quant::units::distance
{

    class Distance;

    struct Domain
    {
        using State = Distance;
    };

}  // namespace quant::units::distance

namespace quant
{

    using units::distance::Distance;

}  // namespace quant
