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
        milli_meters_per_second(double milli_meters_per_second)
        {
            return {milli_meters_per_second};
        }

        static Speed
        meters_per_second(double meters_per_second)
        {
            return {meters_per_second * m2mm};
        }

        std::string
        toString() const;

        double
        to_milli_meters_per_second() const
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
