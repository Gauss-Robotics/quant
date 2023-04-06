#pragma once

#include <string_view>

namespace quant::units::momentum::constants
{

    namespace names
    {
        constexpr std::string_view linear_momentum = "Linear Momentum";
        constexpr std::string_view angular_momentum = "Angular Momentum";
        constexpr std::string_view spatial_momentum = "Spatial Momentum";
        constexpr std::string_view linear_momentum_difference = "Linear Momentum Difference";
        constexpr std::string_view angular_momentum_difference = "Angular Momentum Difference";
        constexpr std::string_view spatial_momentum_difference = "Spatial Momentum Difference";

        constexpr std::string_view kilogram_meters_per_second = "Kilogram Meters per Second";

    }  // namespace names

    namespace symbols
    {

        constexpr std::string_view kilogram_meters_per_second = "kg⋅m/s";

    }  // namespace symbols

}  // namespace quant::units::momentum::constants
