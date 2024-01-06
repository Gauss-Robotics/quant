#pragma once

#include <quant/geometry/ScalarState.h>
#include <quant/units/Scalar.h>
#include <quant/units/mass/constants.h>
#include <quant/units/mass/forward_declarations.h>

#include <ostream>
#include <string>

namespace quant::units::mass
{

    class Mass : public geometry::ScalarState<Mass>
    {

    public:
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
            return {_representation * constants::kg2mg,
                    constants::names::mass,
                    constants::symbols::milligrams};
        };

        Scalar
        to_grams() const
        {
            return {_representation * constants::kg2g,
                    constants::names::mass,
                    constants::symbols::grams};
        }

        Scalar
        to_kilograms() const
        {
            return {_representation, constants::names::mass, constants::symbols::kilograms};
        }

        std::string
        to_string() const
        {
            Scalar (Mass::*member_function_ptr)();

            for (auto fn : {&Mass::to_kilograms, &Mass::to_grams})
            {
                Scalar s = (this->*fn)();
                if (s.value > 1)
                {
                    return s.to_string();
                }
            }

            return to_milligrams().to_string();
        }

        using geometry::ScalarState<Mass>::ScalarState;
    };

    inline std::ostream&
    operator<<(std::ostream& out, Mass const& rhs)
    {
        return out << rhs.to_string();
    }

}  // namespace quant::units::mass
