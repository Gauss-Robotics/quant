#pragma once

#include <quant/geometry/ScalarState.h>
#include <quant/units/speed_fwd.h>
#include <quant/units/velocity_fwd.h>

#include <cstdint>
#include <ostream>
#include <string>

namespace quant::units::speed
{

    constexpr double m2mm = 1'000;

    class Speed : public geometry::ScalarState<Domain>
    {

    public:
        Speed(quant::units::velocity::LinearVelocity const& vel);

        static Speed
        milliMetersPerSecond(double milliMetersPerSecond)
        {
            return {milliMetersPerSecond};
        }

        static Speed
        metersPerSecond(double metersPerSecond)
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
        using geometry::ScalarState<Domain>::ScalarState;  // TODO(dreher): Remove?
    };

    std::ostream&
    operator<<(std::ostream& out, Speed const& rhs);

}  // namespace quant::units::speed
