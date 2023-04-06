#pragma once

namespace quant::units::temperature
{

    class Temperature;
    class TemperatureDifference;

    struct Domain
    {
        using State = Temperature;
        using Difference = TemperatureDifference;
    };

}  // namespace quant::units::temperature

namespace quant
{

    using units::temperature::Temperature;
    using units::temperature::TemperatureDifference;

}  // namespace quant
