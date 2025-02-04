#pragma once

#include <string_view>

namespace quant::units::velocity::constants
{

    namespace names
    {

        constexpr std::string_view linear_velocity = "Linear Velocity";
        constexpr std::string_view angular_velocity = "Angular Velocity";
        constexpr std::string_view twist = "Twist";
        constexpr std::string_view linear_velocity_difference = "Linear Velocity Difference";
        constexpr std::string_view angular_velocity_difference = "Angular Velocity Difference";
        constexpr std::string_view twist_difference = "Twist Difference";

        constexpr std::string_view millimeters_per_second = "Millimeters per Second";
        constexpr std::string_view meters_per_second = "Meters per Second";
        constexpr std::string_view radians_per_second = "Radians per Second";

    }  // namespace names

    namespace symbols
    {

        constexpr std::string_view millimeters_per_second = "mm/s";
        constexpr std::string_view meters_per_second = "m/s";
        constexpr std::string_view radians_per_second = "rad/s";
        constexpr std::string_view degrees_per_second = "°/s";

    }  // namespace symbols

    constexpr double mps2mmps = 1e3;
    constexpr double mmps2mps = 1e-3;

}  // namespace quant::units::velocity::constants
