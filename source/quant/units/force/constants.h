#pragma once

#include <string_view>

namespace quant::units::force::constants
{

    namespace names
    {
        constexpr std::string_view force = "Force";
        constexpr std::string_view torque = "Torque";
        constexpr std::string_view wrench = "Wrench";
        constexpr std::string_view force_difference = "Force Difference";
        constexpr std::string_view torque_difference = "Torque Difference";
        constexpr std::string_view wrench_difference = "Wrench Difference";

        constexpr std::string_view newton = "Newton";
        constexpr std::string_view newton_meters = "Newton Meters";

    }  // namespace names

    namespace symbols
    {

        constexpr std::string_view newton = "N";
        constexpr std::string_view newton_meters = "Nm";

    }  // namespace symbols

}  // namespace quant::units::force::constants
