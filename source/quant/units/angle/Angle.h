#pragma once

#include <quant/geometry/Scalar.h>
#include <quant/geometry/ScalarState.h>
#include <quant/units/Scalar.h>
#include <quant/units/angle/constants.h>
#include <quant/units/angle/forward_declarations.h>

#include <string>

namespace quant::units::angle
{

    class Angle : public geometry::ScalarState<Angle>
    {
    public:
        static Angle
        radians(geometry::Scalar radians)
        {
            return {radians};
        }

        static Angle
        degrees(geometry::Scalar degrees)
        {
            return {degrees * constants::deg2rad};
        }

        std::string
        to_string() const
        {
            return to_radians().to_string();
        }

        Scalar
        to_radians() const
        {
            return {_representation, constants::names::radians, constants::symbols::radians};
        }

        Scalar
        to_degrees() const
        {
            return {_representation * constants::rad2deg,
                    constants::names::degrees,
                    constants::symbols::degrees};
        }

    protected:
        using geometry::ScalarState<Angle>::ScalarState;
    };

    inline std::ostream&
    operator<<(std::ostream& out, Angle const& rhs)
    {
        return out << rhs.to_string();
    }

}  // namespace quant::units::angle
