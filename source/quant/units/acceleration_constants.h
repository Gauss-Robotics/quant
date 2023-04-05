#pragma once

#include <string_view>

namespace quant::units::acceleration::constants
{

    constexpr std::string_view linear_acceleration_name = "Linear Acceleration";
    constexpr std::string_view angular_acceleration_name = "Angular Acceleration";
    constexpr std::string_view spatial_acceleration_name = "Spatial Acceleration";
    constexpr std::string_view linear_acceleration_difference_name =
        "Linear Acceleration Difference";
    constexpr std::string_view angular_acceleration_difference_name =
        "Angular Acceleration Difference";
    constexpr std::string_view spatial_acceleration_difference_name =
        "Spatial Acceleration Difference";

    constexpr std::string_view millimeters_per_second_squared = "mm/s²";
    constexpr std::string_view meters_per_second_squared = "m/s²";

    constexpr double mpss2mmpss = 1e3;
    constexpr double mmpss2mpss = 1e-3;

}  // namespace quant::units::acceleration::constants
