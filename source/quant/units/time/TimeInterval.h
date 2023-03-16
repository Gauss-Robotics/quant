#pragma once


#include <cstdint>
#include <ostream>
#include <string>


namespace quant::units::time
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

} // namespace quant::units::time


namespace quant
{
    using units::time::TimeInterval;
} // namespace quant
