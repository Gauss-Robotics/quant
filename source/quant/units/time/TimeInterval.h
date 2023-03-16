#pragma once


#include <cstdint>
#include <ostream>
#include <string>


namespace simox::core::units::time
{

    /**
     * @brief Represents a duration.
     *
     * API and implementation to match IceUtil::Time (where applicable).
     */
    class TimeInterval
    {

    public:
        /**
         * @brief Constructs a zero-duration.
         */
        TimeInterval();

        // Operators.
    };


    std::ostream& operator<<(std::ostream& out, const TimeInterval& rhs);

} // namespace simox::core::units::time


namespace simox
{
    using core::units::time::TimeInterval;
} // namespace simox
