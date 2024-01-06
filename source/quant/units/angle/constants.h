#pragma once

#include <numbers>
#include <string_view>

namespace quant::units::angle::constants
{

    namespace names
    {

        constexpr std::string_view radians = "Radians";
        constexpr std::string_view degrees = "Degrees";

    }  // namespace names

    namespace symbols
    {

        constexpr std::string_view radians = "rad";
        constexpr std::string_view degrees = "°";

    }  // namespace symbols

    constexpr double deg2rad = std::numbers::pi / 180.;
    constexpr double rad2deg = 180. / std::numbers::pi;

}  // namespace quant::units::angle::constants
