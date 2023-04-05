#pragma once

#include <string_view>

namespace quant::units::velocity::constants
{

    constexpr std::string_view linear_velocity_name = "Linear Velocity";
    constexpr std::string_view angular_velocity_name = "Angular Velocity";
    constexpr std::string_view twist_name = "Twist";
    constexpr std::string_view linear_velocity_difference_name = "Linear Velocity Difference";
    constexpr std::string_view angular_velocity_difference_name = "Angular Velocity Difference";
    constexpr std::string_view twist_difference_name = "Twist Difference";

    constexpr std::string_view millimeters_per_second = "mm/s";
    constexpr std::string_view meters_per_second = "m/s";
    constexpr std::string_view radians_per_second = "rad/s";

    constexpr double mps2mmps = 1e3;
    constexpr double mmps2mps = 1e-3;

}  // namespace quant::units::velocity::constants
