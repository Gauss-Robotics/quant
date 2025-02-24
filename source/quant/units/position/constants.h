#pragma once

#include <string_view>

namespace quant::units::position::constants
{

    namespace names
    {

        constexpr std::string_view position = "Position";
        constexpr std::string_view orientation = "Orientation";
        constexpr std::string_view pose = "Pose";
        constexpr std::string_view linear_displacement = "Linear Displacement";
        constexpr std::string_view angular_displacement = "Angular Displacement";
        constexpr std::string_view spatial_displacement = "Spatial Displacement";

        constexpr std::string_view millimeters = "Millimeters";
        constexpr std::string_view meters = "Meters";
        constexpr std::string_view radians = "Radians";

    }  // namespace names

    namespace symbols
    {

        constexpr std::string_view millimeters = "mm";
        constexpr std::string_view meters = "m";
        constexpr std::string_view radians = "rad";
        constexpr std::string_view degrees = "°";

    }  // namespace symbols

    constexpr double m2mm = 1e3;
    constexpr double mm2m = 1e-3;

}  // namespace quant::units::position::constants
