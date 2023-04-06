#pragma once

#include <string_view>

namespace quant::units::jerk::constants
{

    namespace names
    {

        constexpr std::string_view linear_jerk = "Linear Jerk";
        constexpr std::string_view angular_jerk = "Angular Jerk";
        constexpr std::string_view spatial_jerk = "Spatial Jerk";
        constexpr std::string_view linear_jerk_difference = "Linear Jerk Difference";
        constexpr std::string_view angular_jerk_difference = "Angular Jerk Difference";
        constexpr std::string_view spatial_jerk_difference = "Spatial Jerk Difference";

        constexpr std::string_view millimeters_per_second_cubed = "Millimeters per Second Cubed";
        constexpr std::string_view meters_per_second_cubed = "Meters per Second Cubed";

    }  // namespace names

    namespace symbols
    {

        constexpr std::string_view millimeters_per_second_cubed = "mm/s³";
        constexpr std::string_view meters_per_second_cubed = "m/s³";
        constexpr std::string_view radians_per_second_cubed = "rad/s³";

    }  // namespace symbols

    constexpr double mpsc2mmpsc = 1e3;
    constexpr double mmpsc2mpsc = 1e-3;

}  // namespace quant::units::jerk::constants
