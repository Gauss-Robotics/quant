#pragma once

#include <string_view>

namespace quant::units::momentum::constants
{

    namespace names
    {
        constexpr std::string_view linear_momentum = "Linear Momentum";
        constexpr std::string_view angular_momentum = "Angular Momentum";
        constexpr std::string_view spatial_momentum = "Spatial Momentum";
        constexpr std::string_view linear_impulse = "Linear Impulse";
        constexpr std::string_view angular_impulse = "Angular Impulse";
        constexpr std::string_view spatial_impulse = "Spatial Impulse";

        constexpr std::string_view kilogram_meters_per_second = "Kilogram Meters per Second";
        constexpr std::string_view newton_seconds = "Newton Seconds";
        constexpr std::string_view kilogram_meters_squared_per_second =
            "Kilogram Meters Squared per Second";
        constexpr std::string_view newton_meter_seconds = "Newton Meter Seconds";

    }  // namespace names

    namespace symbols
    {

        constexpr std::string_view kilogram_meters_per_second = "kg⋅m/s";
        constexpr std::string_view newton_seconds = "Ns";
        constexpr std::string_view kilogram_meters_squared_per_second = "kg⋅m²/s";
        constexpr std::string_view newton_meter_seconds = "Nms";

    }  // namespace symbols

}  // namespace quant::units::momentum::constants
