#pragma once


#include <cstdint>
#include <ostream>
#include <string>

#include <quant/geometry/VectorQuantity.h>


namespace quant::units::speed
{

    constexpr double m2mm = 1'000;


    class Speed : geometry::Magnitude<Speed>
    {

    public:
        static Speed
        MilliMetersPerSecond(double milliMetersPerSecond)
        {
            return {milliMetersPerSecond};
        }

        static Speed
        MetersPerSecond(double metersPerSecond)
        {
            return {metersPerSecond * m2mm};
        }

        std::string toString() const;

        double
        toMilliMetersPerSecond() const
        {
            return representation_;
        }

        // Operators.

    protected:
        using geometry::Magnitude<Speed>::Magnitude;
    };


    std::ostream& operator<<(std::ostream& out, const Speed& rhs);

} // namespace quant::units::speed


namespace quant
{
    using units::speed::Speed;
} // namespace quant
