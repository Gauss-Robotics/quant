#pragma once

#include <string_view>

namespace quant::units::speed::constants
{

    namespace names
    {

        constexpr std::string_view speed = "Speed";
        constexpr std::string_view speed_difference = "Speed Difference";

        constexpr std::string_view millimeters_per_second = "Millimeters per Second";
        constexpr std::string_view meters_per_second = "Meters per Second";

    }  // namespace names

    namespace symbols
    {

        constexpr std::string_view millimeters_per_second = "mm/s";
        constexpr std::string_view meters_per_second = "m/s";

    }  // namespace symbols

    constexpr double mps2mmps = 1e3;
    constexpr double mmps2mps = 1e-3;

}  // namespace quant::units::speed::constants
