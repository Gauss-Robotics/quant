#pragma once

#include <string_view>

namespace quant::units::position::constants
{

    constexpr std::string_view position_name = "Position";
    constexpr std::string_view orientation_name = "Orientation";
    constexpr std::string_view pose_name = "Pose";
    constexpr std::string_view linear_displacement_name = "Linear Displacement";
    constexpr std::string_view angular_displacement_name = "Angular Displacement";
    constexpr std::string_view spatial_displacement_name = "Spatial Displacement";

    constexpr std::string_view millimeters = "mm";
    constexpr std::string_view meters = "m";
    constexpr std::string_view radians = "rad";

    constexpr double m2mm = 1e3;
    constexpr double mm2m = 1e-3;

}  // namespace quant::units::position::constants
