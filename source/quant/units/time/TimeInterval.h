#pragma once

#include <cstdint>
#include <ostream>
#include <string>

namespace quant::units::time
{

    /**
     * @brief Represents a time interval.
     */
    class TimeInterval
    {

    public:
        TimeInterval();

        // Operators.
    };

    std::ostream&
    operator<<(std::ostream& out, TimeInterval const& rhs);

}  // namespace quant::units::time

namespace quant
{
    using units::time::TimeInterval;
}  // namespace quant
