#pragma once

#include <quant/geometry/ScalarState.h>
#include <quant/units/Scalar.h>
#include <quant/units/temperature/constants.h>
#include <quant/units/temperature_fwd.h>

#include <cstdint>
#include <ostream>
#include <string>

namespace quant::units::temperature
{

    class Temperature : public geometry::ScalarState<Domain>
    {

    public:
        static Temperature
        degrees_celcius(geometry::Scalar celsius)
        {
            return {celsius};
        }

        static Temperature
        kelvin(geometry::Scalar kelvin)
        {
            return {kelvin + constants::k2c_offset};
        }

        static Temperature
        degrees_fahrenheit(geometry::Scalar fahrenheit)
        {
            return {(fahrenheit + constants::f2c_offset) * constants::f2c_factor};
        }

        static Temperature
        degrees_rankine(geometry::Scalar rankine)
        {
            return {(rankine + constants::ra2c_offset) * constants::ra2c_factor};
        }

        std::string
        to_string() const
        {
            return to_degrees_celsius().to_string();
        }

        Scalar
        to_degrees_celsius() const
        {
            return {
                _representation, constants::names::temperature, constants::symbols::degree_celsius};
        }

        Scalar
        to_kelvin() const
        {
            return {_representation + constants::c2k_offset,
                    constants::names::temperature,
                    constants::symbols::kelvin};
        }

        Scalar
        to_degrees_fahrenheit() const
        {
            return {_representation * constants::c2f_factor + constants::c2f_offset,
                    constants::names::temperature,
                    constants::symbols::degree_fahrenheit};
        }

        Scalar
        to_degrees_rankine() const
        {
            return {_representation * constants::c2ra_factor + constants::c2ra_offset,
                    constants::names::temperature,
                    constants::symbols::degree_rankine};
        }

        using geometry::ScalarState<Domain>::ScalarState;
    };

    inline std::ostream&
    operator<<(std::ostream& out, Temperature const& rhs)
    {
        return out << rhs.to_string();
    }

}  // namespace quant::units::temperature
