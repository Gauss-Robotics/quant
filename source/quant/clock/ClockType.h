#pragma once

#include <quantUtility/meta/enum/EnumNames.hpp>


namespace quant::time
{

    /**
     * @brief Describes the type of clock.
     */
    enum class ClockType
    {
        /// Normalized time as reported by the operating system.
        Realtime,
        /// Monotonic/steady clock of the operating system.
        Monotonic,
        /// Time given by time server if configured, realtime otherwise.
        Virtual,
        /// Unknown source of time.
        Unknown
    };


    extern const quant::meta::EnumNames<ClockType> ClockTypeNames;

} // namespace quant::time


namespace quant
{
    using core::time::ClockType;
    using core::time::ClockTypeNames;
} // namespace quant
