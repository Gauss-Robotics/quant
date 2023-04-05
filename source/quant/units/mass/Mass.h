#pragma once

#include <quant/geometry/ScalarState.h>
#include <quant/units/Scalar.h>
#include <quant/units/mass_constants.h>
#include <quant/units/mass_fwd.h>

#include <ostream>
#include <string>

namespace quant::units::mass
{

    class Mass : public geometry::ScalarState<Domain>
    {

    public:
        Mass();

        static Mass
        milligrams(geometry::Scalar milligrams)
        {
            return {milligrams * constants::mg2kg};
        }

        static Mass
        grams(geometry::Scalar grams)
        {
            return {grams * constants::g2kg};
        }

        static Mass
        kilograms(geometry::Scalar kilograms)
        {
            return {kilograms};
        }

        Scalar
        to_milligrams() const
        {
            return {
                _representation * constants::kg2mg, constants::mass_name, constants::milligrams};
        };

        Scalar
        to_grams() const
        {
            return {_representation * constants::kg2g, constants::mass_name, constants::grams};
        }

        Scalar
        to_kilograms() const
        {
            return {_representation, constants::mass_name, constants::kilograms};
        }

    private:
        using geometry::ScalarState<Domain>::ScalarState;
    };

    std::ostream&
    operator<<(std::ostream& out, Mass const& rhs);

}  // namespace quant::units::mass
