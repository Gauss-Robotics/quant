#pragma once

#include <quant/geometry/Scalar.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry_fwd.h>

#include <sstream>
#include <typeinfo>

namespace quant::geometry
{

    template <typename Domain>
    class ScalarState
    {
    public:
        // Construct.

        ScalarState() : _representation{0}
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

            out << "value=" << _representation;

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
            return _representation == rhs.representation_;
        }

        bool
        operator!=(typename Domain::State const& rhs) const
        {
            return _representation != rhs.representation_;
        }

        bool
        is_approx(typename Domain::State const& rhs, double tolerance) const
        {
            return std::abs(_representation - rhs.representation_) < tolerance;
        }

        using GeometricRepresentationType = double;
        using GeometricType = traits::StateType;

    protected:
        ScalarState(Scalar scalar) : _representation{scalar}
        {
            ;
        }

        Scalar
        to_scalar() const
        {
            return _representation;
        }

        double _representation;

        friend class detail::QuantityAccessor<typename Domain::State>;
    };

}  // namespace quant::geometry
