#pragma once

#include <string_view>

namespace quant::units::time::constants
{

    constexpr std::string_view microseconds = "µs";
    constexpr std::string_view milliseconds = "ms";
    constexpr std::string_view seconds = "s";
    constexpr std::string_view minutes = "min";
    constexpr std::string_view hours = "h";
    constexpr std::string_view days = "d";

    constexpr double d2h = 24;
    constexpr double h2m = 60;
    constexpr double m2s = 60;
    constexpr double s2ms = 1e3;
    constexpr double ms2us = 1e3;
    constexpr double us2ms = 1. / ms2us;
    constexpr double ms2s = 1. / s2ms;
    constexpr double s2m = 1. / m2s;
    constexpr double m2h = 1. / h2m;
    constexpr double h2d = 1. / d2h;

    constexpr double s2us = s2ms * ms2us;
    constexpr double m2us = m2s * s2us;
    constexpr double h2us = h2m * m2us;
    constexpr double d2us = d2h * h2us;
    constexpr double us2s = us2ms * ms2s;
    constexpr double us2m = us2s * s2m;
    constexpr double us2h = us2m * m2h;
    constexpr double us2d = us2h * h2d;

}  // namespace quant::units::time::constants
