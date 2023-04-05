#pragma once

#include <string_view>

namespace quant::units::force::constants
{

    constexpr std::string_view force_name = "Force";
    constexpr std::string_view torque_name = "Torque";
    constexpr std::string_view wrench_name = "Wrench";
    constexpr std::string_view force_difference_name = "ForceDifference";
    constexpr std::string_view torque_difference_name = "TorqueDifference";
    constexpr std::string_view wrench_difference_name = "WrenchDifference";

    constexpr std::string_view newton = "N";
    constexpr std::string_view newton_meters = "Nm";

}  // namespace quant::units::force::constants
