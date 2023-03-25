#pragma once

namespace quant::units::temperature
{

    class Temperature;

    struct Domain
    {
        using State = Temperature;
    };

}  // namespace quant::units::temperature

namespace quant
{

    using units::temperature::Temperature;

}  // namespace quant
