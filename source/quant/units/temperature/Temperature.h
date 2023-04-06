#pragma once

#include <quant/geometry/ScalarState.h>
#include <quant/units/Scalar.h>
#include <quant/units/temperature_constants.h>
#include <quant/units/temperature_fwd.h>

#include <cstdint>
#include <ostream>
#include <string>

namespace quant::units::temperature
{

    class Temperature : geometry::ScalarState<Domain>
    {

    public:
        static Temperature
        degree_celcius(geometry::Scalar celsius)
        {
            return {celsius};
        }

        static Temperature
        kelvin(geometry::Scalar kelvin)
        {
            return {kelvin + constants::k2c_offset};
        }

        static Temperature
        degree_fahrenheit(geometry::Scalar fahrenheit)
        {
            return {(fahrenheit + constants::f2c_offset) * constants::f2c_factor};
        }

        static Temperature
        degree_rankine(geometry::Scalar rankine)
        {
            return {(rankine + constants::ra2c_offset) * constants::ra2c_factor};
        }

        std::string
        to_string() const;

        Scalar
        to_degree_celsius() const
        {
            return {_representation, constants::temperature_name, constants::degree_celsius};
        }

        Scalar
        to_kelvin() const
        {
            return _representation + constants::c2k_offset;
        }

        Scalar
        to_degree_fahrenheit() const
        {
            return _representation * constants::c2f_factor + constants::c2f_offset;
        }

        Scalar
        to_degree_rankine() const
        {
            return _representation * constants::c2f_factor + constants::c2ra_offset;
        }

        // Operators.

    protected:
        using geometry::ScalarState<Domain>::ScalarState;
    };

    std::ostream&
    operator<<(std::ostream& out, Temperature const& rhs);

}  // namespace quant::units::temperature
