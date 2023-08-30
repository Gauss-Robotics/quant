#pragma once

#include <string_view>

namespace quant::units::time::constants
{

    namespace names
    {

        constexpr std::string_view time_point = "Time Point";
        constexpr std::string_view duration = "Duration";
        constexpr std::string_view frequency = "Frequency";

        constexpr std::string_view nanoseconds = "Nanoseconds";
        constexpr std::string_view microseconds = "Microseconds";
        constexpr std::string_view milliseconds = "Milliseconds";
        constexpr std::string_view seconds = "Seconds";
        constexpr std::string_view minutes = "Minutes";
        constexpr std::string_view hours = "Hours";
        constexpr std::string_view days = "Days";

        constexpr std::string_view microhertz = "Microhertz";
        constexpr std::string_view millihertz = "Millihertz";
        constexpr std::string_view hertz = "Hertz";
        constexpr std::string_view kilohertz = "Kilohertz";
        constexpr std::string_view megahertz = "Megahertz";

    }  // namespace names

    namespace symbols
    {

        constexpr std::string_view nanoseconds = "ns";
        constexpr std::string_view microseconds = "µs";
        constexpr std::string_view milliseconds = "ms";
        constexpr std::string_view seconds = "s";
        constexpr std::string_view minutes = "min";
        constexpr std::string_view hours = "h";
        constexpr std::string_view days = "d";

        constexpr std::string_view microhertz = "µHz";
        constexpr std::string_view millihertz = "mHz";
        constexpr std::string_view hertz = "Hz";
        constexpr std::string_view kilohertz = "kHz";
        constexpr std::string_view megahertz = "MHz";

    }  // namespace symbols

    constexpr double d2h = 24;
    constexpr double h2min = 60;
    constexpr double min2s = 60;
    constexpr double s2ms = 1e3;
    constexpr double ms2us = 1e3;
    constexpr double us2ns = 1e3;
    constexpr double ns2us = 1. / us2ns;
    constexpr double us2ms = 1. / ms2us;
    constexpr double ms2s = 1. / s2ms;
    constexpr double s2min = 1. / min2s;
    constexpr double min2h = 1. / h2min;
    constexpr double h2d = 1. / d2h;

    constexpr double s2us = s2ms * ms2us;
    constexpr double min2us = min2s * s2us;
    constexpr double h2us = h2min * min2us;
    constexpr double d2us = d2h * h2us;
    constexpr double us2s = us2ms * ms2s;
    constexpr double us2min = us2s * s2min;
    constexpr double us2h = us2min * min2h;
    constexpr double us2d = us2h * h2d;

    constexpr double MHz2kHz = 1e3;
    constexpr double kHz2Hz = 1e3;
    constexpr double Hz2mHz = 1e3;
    constexpr double mHz2uHz = 1e3;
    constexpr double Hz2uHz = Hz2mHz * mHz2uHz;
    constexpr double kHz2uHz = kHz2Hz * Hz2uHz;
    constexpr double MHz2uHz = MHz2kHz * kHz2uHz;

}  // namespace quant::units::time::constants
