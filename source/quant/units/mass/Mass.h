#pragma once

#include <quant/geometry/ScalarState.h>
#include <quant/units/mass_fwd.h>

#include <ostream>
#include <string>

namespace quant::units::mass
{

    constexpr double mg2kg = 1e-6;
    constexpr double g2kg = 1e-3;
    constexpr double kg2g = 1e3;
    constexpr double kg2mg = 1e6;

    class Mass : public geometry::ScalarState<Domain>
    {

    public:
        Mass();

        static Mass
        milligrams(double milligrams)
        {
            return {milligrams * mg2kg};
        }

        static Mass
        grams(double grams)
        {
            return {grams * g2kg};
        }

        static Mass
        kilograms(double kilograms)
        {
            return {kilograms};
        }

        double
        to_milligrams() const
        {
            return representation_ * kg2mg;
        }

        double
        to_grams() const
        {
            return representation_ * kg2g;
        }

        double
        to_kilograms() const
        {
            return representation_;
        }

    private:
        using geometry::ScalarState<Domain>::ScalarState;
    };

    std::ostream&
    operator<<(std::ostream& out, Mass const& rhs);

}  // namespace quant::units::mass
