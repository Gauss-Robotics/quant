#pragma once

#include <string_view>

namespace quant::units::speed::constants
{

    constexpr std::string_view speed_name = "Speed";
    constexpr std::string_view speed_difference_name = "Speed Difference";

    constexpr std::string_view millimeters_per_second = "mm/s";
    constexpr std::string_view meters_per_second = "m/s";

    constexpr double mps2mmps = 1e3;
    constexpr double mmps2mps = 1e-3;

}  // namespace quant::units::speed::constants
