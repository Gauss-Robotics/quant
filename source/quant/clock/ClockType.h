#pragma once

#include <SimoxUtility/meta/enum/EnumNames.hpp>


namespace simox::core::time
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


    extern const simox::meta::EnumNames<ClockType> ClockTypeNames;

} // namespace simox::core::time


namespace simox
{
    using core::time::ClockType;
    using core::time::ClockTypeNames;
} // namespace simox
