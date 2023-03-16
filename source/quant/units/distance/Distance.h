#pragma once


#include <cstdint>
#include <ostream>
#include <string>

#include <quant/geometry/ScalarQuantity.h>


namespace quant::units::distance
{

    constexpr double m2mm = 1'000;


    class Distance : geometry::ScalarQuantity<Distance>
    {

    public:
        static Distance
        MilliMeters(double milliMeters)
        {
            return {milliMeters};
        }

        static Distance
        Meters(double meters)
        {
            return {meters * m2mm};
        }

        std::string toString() const;

        double
        toMilliMeters() const
        {
            return representation_;
        }

        // Operators.

    protected:
        using geometry::ScalarQuantity<Distance>::ScalarQuantity;
    };


    std::ostream& operator<<(std::ostream& out, const Distance& rhs);

} // namespace quant::units::distance


namespace quant
{
    using units::distance::Distance;
} // namespace quant
