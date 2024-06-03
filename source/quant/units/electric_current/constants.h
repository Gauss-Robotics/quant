#pragma once

#include <string_view>

namespace quant::units::electric_current::constants
{

    namespace names
    {

        constexpr std::string_view current = "Current";
        constexpr std::string_view temperature_difference = "Current Difference";

        constexpr std::string_view ampere = "Ampere";
        constexpr std::string_view milliampere = "Milliampere";

    }  // namespace names

    namespace symbols
    {

        constexpr std::string_view milliampere = "mA";
        constexpr std::string_view ampere = "A";

    }  // namespace symbols

    constexpr double A2mA = 1e3;
    constexpr double mA2A = 1. / A2mA;

}  // namespace quant::units::electric_current::constants
