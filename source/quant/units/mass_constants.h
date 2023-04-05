#pragma once

#include <string_view>

namespace quant::units::mass::constants
{

    constexpr std::string_view mass_name = "Mass";

    constexpr std::string_view milligrams = "mg";
    constexpr std::string_view grams = "g";
    constexpr std::string_view kilograms = "kg";

    constexpr double kg2mg = 1e6;
    constexpr double kg2g = 1e3;
    constexpr double g2kg = 1e-3;
    constexpr double mg2kg = 1e-6;

}  // namespace quant::units::mass::constants
