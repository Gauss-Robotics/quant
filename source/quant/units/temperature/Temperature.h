#pragma once

#include <quant/geometry/ScalarQuantity.h>
#include <quant/units/temperature_fwd.h>

#include <cstdint>
#include <ostream>
#include <string>

namespace quant::units::temperature
{

    constexpr double celsius2kelvinOffset = 273.15;
    constexpr double celsius2fahrenheitFactor = 9. / 5.;
    constexpr double celsius2fahrenheitOffset = 32;

    constexpr double kelvin2celsiusOffset = -celsius2kelvinOffset;
    constexpr double fahrenheit2celsiusFactor = 5. / 9.;
    constexpr double fahrenheit2celsiusOffset = -celsius2fahrenheitOffset;
    constexpr double fahrenheit2rankineOffset = 459.67;

    constexpr double celsius2rankineOffset = celsius2fahrenheitOffset + fahrenheit2rankineOffset;
    constexpr double rankine2celsiusOffset = -celsius2rankineOffset;
    constexpr double rankine2celsiusFactor = fahrenheit2celsiusFactor;

    class Temperature : geometry::ScalarQuantity<Domain>
    {

    public:
        static Temperature
        degreeCelcius(double celsius)
        {
            return {celsius};
        }

        static Temperature
        kelvin(double kelvin)
        {
            return {kelvin + kelvin2celsiusOffset};
        }

        static Temperature
        degreeFahrenheit(double fahrenheit)
        {
            return {(fahrenheit + fahrenheit2celsiusOffset) * fahrenheit2celsiusFactor};
        }

        static Temperature
        degreeRankine(double rankine)
        {
            return {(rankine + rankine2celsiusOffset) * rankine2celsiusFactor};
        }

        std::string
        toString() const;

        double
        toDegreeCelsius() const
        {
            return representation_;
        }

        double
        toKelvin() const
        {
            return representation_ + celsius2kelvinOffset;
        }

        double
        toDegreeFahrenheit() const
        {
            return representation_ * celsius2fahrenheitFactor + celsius2fahrenheitOffset;
        }

        double
        toDegreeRankine() const
        {
            return representation_ * celsius2fahrenheitFactor + celsius2rankineOffset;
        }

        // Operators.

    protected:
        using geometry::ScalarQuantity<Domain>::ScalarQuantity;
    };

    std::ostream&
    operator<<(std::ostream& out, Temperature const& rhs);

}  // namespace quant::units::temperature
