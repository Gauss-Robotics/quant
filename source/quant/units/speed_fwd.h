#pragma once

namespace quant::units::speed
{

    class Speed;

    struct Domain
    {
        using State = Speed;
    };

}  // namespace quant::units::speed

namespace quant
{

    using units::speed::Speed;

}  // namespace quant
