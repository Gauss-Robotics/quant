#pragma once

#include <quant/geometry/ScalarQuantity.h>

#include <cstdint>
#include <ostream>
#include <string>

namespace quant::units::velocity
{

    class LinearVelocity;

}

namespace quant::units::speed
{

    constexpr double m2mm = 1'000;

    class Speed : public geometry::ScalarQuantity<Speed>
    {

    public:
        Speed(quant::units::velocity::LinearVelocity const& vel);

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

        std::string
        toString() const;

        double
        toMilliMetersPerSecond() const
        {
            return representation_;
        }

        // Operators.

    protected:
        using geometry::ScalarQuantity<Speed>::ScalarQuantity;
    };

    std::ostream&
    operator<<(std::ostream& out, Speed const& rhs);

}  // namespace quant::units::speed

namespace quant
{

    using units::speed::Speed;

}  // namespace quant
