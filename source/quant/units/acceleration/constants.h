#pragma once

#include <string_view>

namespace quant::units::acceleration::constants
{

    namespace names
    {

        constexpr std::string_view linear_acceleration = "Linear Acceleration";
        constexpr std::string_view angular_acceleration = "Angular Acceleration";
        constexpr std::string_view spatial_acceleration = "Spatial Acceleration";
        constexpr std::string_view linear_acceleration_difference =
            "Linear Acceleration Difference";
        constexpr std::string_view angular_acceleration_difference =
            "Angular Acceleration Difference";
        constexpr std::string_view spatial_acceleration_difference =
            "Spatial Acceleration Difference";

        constexpr std::string_view millimeters_per_second_squared =
            "Millimeters per Second Squared";
        constexpr std::string_view meters_per_second_squared = "Meters per Second Squared";

    }  // namespace names

    namespace symbols
    {

        constexpr std::string_view millimeters_per_second_squared = "mm/s²";
        constexpr std::string_view meters_per_second_squared = "m/s²";
        constexpr std::string_view radians_per_second_squared = "rad/s²";

    }  // namespace symbols

    constexpr double mpss2mmpss = 1e3;
    constexpr double mmpss2mpss = 1e-3;

}  // namespace quant::units::acceleration::constants
