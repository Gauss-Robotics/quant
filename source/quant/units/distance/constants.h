#pragma once

#include <string_view>

namespace quant::units::distance::constants
{

    namespace names
    {

        constexpr std::string_view distance = "Distance";

        constexpr std::string_view millimeters = "Millimeters";
        constexpr std::string_view meters = "Meters";

    }  // namespace names

    namespace symbols
    {

        constexpr std::string_view millimeters = "mm";
        constexpr std::string_view meters = "m";

    }  // namespace symbols

    constexpr double m2mm = 1e3;
    constexpr double mm2m = 1e-3;

}  // namespace quant::units::distance::constants
