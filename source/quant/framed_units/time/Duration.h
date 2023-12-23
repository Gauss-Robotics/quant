#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/framed_units/time/forward_declarations.h>
#include <quant/units/time/Duration.h>

namespace quant::framed_units::time
{

    class Duration : public Framed<units::time::Duration>
    {
    public:
        using Framed<units::time::Duration>::Framed;

        /**
         * @brief Returns the amount of microseconds.
         *
         * @return Amount of microseconds.
         */
        units::Scalar
        to_microseconds() const
        {
            return get_framed_object().to_microseconds();
        }

        /**
         * @brief Returns the amount of milliseconds.
         *
         * @return Amount of milliseconds.
         */
        units::Scalar
        to_milliseconds() const
        {
            return get_framed_object().to_milliseconds();
        }

        /**
         * @brief Returns the amount of seconds.
         *
         * @return Amount of seconds.
         */
        units::Scalar
        to_seconds() const
        {
            return get_framed_object().to_seconds();
        }

        std::string
        to_string() const
        {
            return get_framed_object().to_string();
        }
    };

    inline std::ostream&
    operator<<(std::ostream& os, framed_units::time::Duration const& rhs)
    {
        return os << rhs.to_string();
    }

}  // namespace quant::framed_units::time
