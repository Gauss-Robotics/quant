#pragma once

#include <quant/geometry/ScalarState.h>
#include <quant/units/Scalar.h>
#include <quant/units/time/Duration.h>
#include <quant/units/time/constants.h>
#include <quant/units/time_fwd.h>

#include <cstdint>
#include <ostream>
#include <string>

namespace quant::units::time
{

    /**
     * @brief Represents a frequency.
     */
    class Frequency : public geometry::ScalarState<Frequency, std::int64_t>
    {
        // Construct.
    public:
        static Frequency
        hertz(geometry::Scalar hertz)
        {
            return {hertz};
        }

        Scalar
        to_hertz() const
        {
            return {_representation, constants::names::frequency, constants::symbols::hertz};
        }

        Duration
        to_period() const
        {
            // TODO: Stub
            return Duration::seconds(1);
        }

        std::string
        to_string() const
        {
            return to_hertz().to_string();
        }

    protected:
        using geometry::ScalarState<Frequency, std::int64_t>::ScalarState;
    };

    inline std::ostream&
    operator<<(std::ostream& out, Frequency const& rhs)
    {
        return out << rhs.to_string();
    }

}  // namespace quant::units::time
