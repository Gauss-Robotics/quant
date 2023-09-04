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
        microhertz(geometry::Scalar microhertz)
        {
            return {microhertz};
        }

        static Frequency
        millihertz(geometry::Scalar millihertz)
        {
            return {millihertz * constants::mHz2uHz};
        }

        static Frequency
        hertz(geometry::Scalar hertz)
        {
            return {hertz * constants::Hz2uHz};
        }

        static Frequency
        kilohertz(geometry::Scalar kilohertz)
        {
            return {kilohertz * constants::kHz2uHz};
        }

        static Frequency
        megahertz(geometry::Scalar megahertz)
        {
            return {megahertz * constants::MHz2uHz};
        }

        Scalar
        to_hertz() const
        {
            return {_representation * constants::uHz2Hz,
                    constants::names::frequency,
                    constants::symbols::hertz};
        }

        Duration
        to_period() const
        {
            return Duration::seconds(1. / to_hertz());
        }

        std::string
        to_string() const
        {
            return to_hertz().to_string();
        }

    protected:
        using geometry::ScalarState<Frequency, std::int64_t>::ScalarState;
    };

    template <typename NumericType>
        requires std::integral<NumericType> or std::floating_point<NumericType>
    inline Frequency
    operator/(NumericType const lhs, quant::Duration const& rhs)
    {
        return Frequency::hertz(static_cast<double>(lhs) / rhs.to_seconds());
    }

    inline std::ostream&
    operator<<(std::ostream& out, Frequency const& rhs)
    {
        return out << rhs.to_string();
    }

}  // namespace quant::units::time
