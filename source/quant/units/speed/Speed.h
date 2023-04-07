#pragma once

#include <quant/geometry/ScalarState.h>
#include <quant/units/Scalar.h>
#include <quant/units/distance/Distance.h>
#include <quant/units/speed/constants.h>
#include <quant/units/speed_fwd.h>
#include <quant/units/time/Duration.h>
#include <quant/units/velocity_fwd.h>

#include <ostream>
#include <string>

namespace quant::units::speed
{

    class Speed : public geometry::ScalarState<Domain>
    {

    public:
        Speed(quant::units::velocity::LinearVelocity const& vel);

        static Speed
        millimeters_per_second(geometry::Scalar millimeters_per_second)
        {
            return {millimeters_per_second};
        }

        static Speed
        meters_per_second(geometry::Scalar meters_per_second)
        {
            return {meters_per_second * constants::mps2mmps};
        }

        Scalar
        to_millimeters_per_second() const
        {
            return {_representation,
                    constants::names::speed,
                    constants::symbols::millimeters_per_second};
        }

        Scalar
        to_meters_per_second() const
        {
            return {_representation * constants::mmps2mps,
                    constants::names::speed,
                    constants::symbols::meters_per_second};
        }

    protected:
        using geometry::ScalarState<Domain>::ScalarState;
    };

    inline std::ostream&
    operator<<(std::ostream& out, Speed const& rhs)
    {
        return out << rhs.to_millimeters_per_second();
    }

}  // namespace quant::units::speed

namespace quant
{

    inline Speed
    operator/(Distance const& lhs, Duration const& rhs)
    {
        return Speed::millimeters_per_second(lhs.to_millimeters() / rhs.to_seconds());
    }

}  // namespace quant
