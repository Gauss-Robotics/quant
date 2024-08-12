#pragma once

#include <quant/geometry/ScalarState.h>
#include <quant/units/Scalar.h>
#include <quant/units/electric_current/constants.h>
#include <quant/units/electric_current/forward_declarations.h>

#include <ostream>
#include <string>

namespace quant::units::electric_current
{

    class Current : public geometry::ScalarState<Current>
    {

    public:
        static Current
        milliampere(geometry::Scalar milliampere)
        {
            return {milliampere * constants::mA2A};
        }

        static Current
        ampere(geometry::Scalar ampere)
        {
            return {ampere};
        }

        std::string
        to_string() const
        {
            if (to_ampere().value > 1)
            {
                return to_ampere().to_string();
            }
            return to_milliampere().to_string();
        }

        Scalar
        to_ampere() const
        {
            return {_representation, constants::names::current, constants::symbols::ampere};
        }

        Scalar
        to_milliampere() const
        {
            return {_representation * constants::A2mA,
                    constants::names::current,
                    constants::symbols::milliampere};
        }

        using geometry::ScalarState<Current>::ScalarState;
    };

    inline std::ostream&
    operator<<(std::ostream& out, Current const& rhs)
    {
        return out << rhs.to_string();
    }

}  // namespace quant::units::electric_current
