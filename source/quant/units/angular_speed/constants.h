#pragma once

#include <string_view>

namespace quant::units::angular_speed::constants
{

    namespace names
    {

        constexpr std::string_view speed = "Angular Speed";
        constexpr std::string_view speed_difference = "Angular Speed Difference";

        constexpr std::string_view radians_per_millisecond = "Radians per Millisecond";
        constexpr std::string_view radians_per_second = "Radians per Second";

    }  // namespace names

    namespace symbols
    {

        constexpr std::string_view radians_per_millisecond = "rad/ms";
        constexpr std::string_view radians_per_second = "rad/s";

    }  // namespace symbols

    constexpr double radpms2radps = 1e3;
    constexpr double radps2radpms = 1e-3;

}  // namespace quant::units::angular_speed::constants
