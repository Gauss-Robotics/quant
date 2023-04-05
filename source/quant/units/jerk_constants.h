#pragma once

#include <string_view>

namespace quant::units::jerk::constants
{

    constexpr std::string_view linear_jerk_name = "Linear Jerk";
    constexpr std::string_view angular_jerk_name = "Angular Jerk";
    constexpr std::string_view spatial_jerk_name = "Spatial Jerk";
    constexpr std::string_view linear_jerk_difference_name = "Linear Jerk Difference";
    constexpr std::string_view angular_jerk_difference_name = "Angular Jerk Difference";
    constexpr std::string_view spatial_jerk_difference_name = "Spatial Jerk Difference";

    constexpr std::string_view millimeters_per_second_cubed = "mm/s³";
    constexpr std::string_view meters_per_second_cubed = "m/s³";

    constexpr double mpsc2mmpsc = 1e3;
    constexpr double mmpsc2mpsc = 1e-3;

}  // namespace quant::units::jerk::constants
