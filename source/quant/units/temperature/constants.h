#pragma once

#include <string_view>

namespace quant::units::temperature::constants
{

    namespace names
    {

        constexpr std::string_view temperature = "Temperature";
        constexpr std::string_view temperature_difference = "Temperature Difference";

        constexpr std::string_view degree_celsius = "Degree Celsius";
        constexpr std::string_view kelvin = "Kelvin";
        constexpr std::string_view degree_fahrenheit = "Degree Fahrenheit";
        constexpr std::string_view degree_rankine = "Degree Rankine";

    }  // namespace names

    namespace symbols
    {

        constexpr std::string_view degree_celsius = "°C";
        constexpr std::string_view kelvin = "K";
        constexpr std::string_view degree_fahrenheit = "°F";
        constexpr std::string_view degree_rankine = "°Ra";

    }  // namespace symbols

    constexpr double c2k_offset = 273.15;
    constexpr double c2f_factor = 9. / 5.;
    constexpr double c2ra_factor = c2f_factor;
    constexpr double c2f_offset = 32;

    constexpr double k2c_offset = -c2k_offset;
    constexpr double f2c_factor = 5. / 9.;
    constexpr double f2c_offset = -c2f_offset;
    constexpr double f2ra_offset = 459.67;

    constexpr double c2ra_offset = c2f_offset + f2ra_offset;
    constexpr double ra2c_offset = -c2ra_offset;
    constexpr double ra2c_factor = f2c_factor;

}  // namespace quant::units::temperature::constants
