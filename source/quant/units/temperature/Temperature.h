#pragma once

#include <quant/geometry/ScalarState.h>
#include <quant/units/temperature_fwd.h>

#include <cstdint>
#include <ostream>
#include <string>

namespace quant::units::temperature
{

    constexpr double celsius2kelvin_offset = 273.15;
    constexpr double celsius2fahrenheit_factor = 9. / 5.;
    constexpr double celsius2fahrenheit_offset = 32;

    constexpr double kelvin2celsius_offset = -celsius2kelvin_offset;
    constexpr double fahrenheit2celsius_factor = 5. / 9.;
    constexpr double fahrenheit2celsius_offset = -celsius2fahrenheit_offset;
    constexpr double fahrenheit2rankine_offset = 459.67;

    constexpr double celsius2rankine_offset = celsius2fahrenheit_offset + fahrenheit2rankine_offset;
    constexpr double rankine2celsius_offset = -celsius2rankine_offset;
    constexpr double rankine2celsius_factor = fahrenheit2celsius_factor;

    class Temperature : geometry::ScalarState<Domain>
    {

    public:
        static Temperature
        degree_celcius(double celsius)
        {
            return {celsius};
        }

        static Temperature
        kelvin(double kelvin)
        {
            return {kelvin + kelvin2celsius_offset};
        }

        static Temperature
        degree_fahrenheit(double fahrenheit)
        {
            return {(fahrenheit + fahrenheit2celsius_offset) * fahrenheit2celsius_factor};
        }

        static Temperature
        degree_rankine(double rankine)
        {
            return {(rankine + rankine2celsius_offset) * rankine2celsius_factor};
        }

        std::string
        to_string() const;

        double
        to_degree_celsius() const
        {
            return _representation;
        }

        double
        to_kelvin() const
        {
            return _representation + celsius2kelvin_offset;
        }

        double
        to_degree_fahrenheit() const
        {
            return _representation * celsius2fahrenheit_factor + celsius2fahrenheit_offset;
        }

        double
        to_degree_rankine() const
        {
            return _representation * celsius2fahrenheit_factor + celsius2rankine_offset;
        }

        // Operators.

    protected:
        using geometry::ScalarState<Domain>::ScalarState;
    };

    std::ostream&
    operator<<(std::ostream& out, Temperature const& rhs);

}  // namespace quant::units::temperature
