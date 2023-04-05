#pragma once

#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry_fwd.h>

#include <sstream>
#include <typeinfo>

namespace quant::geometry
{

    template <typename Domain, typename ScalarType>
    class ScalarState
    {
    public:
        // Construct.

        ScalarState() : representation_{0}
        {
            ;
        }

        static typename Domain::State
        zero()
        {
            return typename Domain::State(0);
        }

        // Convert.

        std::string
        to_string(std::string const& quantity_name = "", std::string const& unit = "") const
        {
            std::stringstream out;
            out << "<";

            if (not quantity_name.empty())
            {
                out << quantity_name << " ";
            }

            out << "value=" << representation_;

            if (not unit.empty())
            {
                out << unit;
            }

            out << ">";
            return out.str();
        }

        // Compare.

        bool
        operator==(typename Domain::State const& rhs) const
        {
            return representation_ == rhs.representation_;
        }

        bool
        operator!=(typename Domain::State const& rhs) const
        {
            return representation_ != rhs.representation_;
        }

        bool
        is_approx(typename Domain::State const& rhs, ScalarType tolerance) const
        {
            return std::abs(representation_ - rhs.representation_) < tolerance;
        }

        using GeometricRepresentationType = ScalarType;
        using GeometricType = traits::StateType;

    protected:
        ScalarState(ScalarType value) : representation_{value}
        {
            ;
        }

        ScalarType
        to_scalar() const
        {
            return representation_;
        }

        ScalarType representation_;

        friend class detail::QuantityAccessor<typename Domain::State>;
    };

}  // namespace quant::geometry
