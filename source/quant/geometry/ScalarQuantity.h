#pragma once

#include <quant/geometry/detail/Accessors.h>
#include <quant/geometry_fwd.h>

#include <sstream>
#include <typeinfo>

namespace quant::geometry
{

    template <typename Domain, typename ScalarType>
    class ScalarQuantity
    {
    public:
        // Construct.

        ScalarQuantity() : representation_{0}
        {
            ;
        }

        static typename Domain::State
        Zero()
        {
            return typename Domain::State(0);
        }

        // Convert.

        ScalarType
        toScalar() const
        {
            return representation_;
        }

        std::string
        toString(std::string const& quantityName = "", std::string const& unit = "") const
        {
            std::stringstream out;
            out << "<";

            if (not quantityName.empty())
            {
                out << quantityName << " ";
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
        isApprox(typename Domain::State const& rhs, ScalarType precision) const
        {
            return std::abs(representation_ - rhs.representation_) < precision;
        }

        using GeometricRepresentationType = ScalarType;
        using GeometricType = ScalarStateType;
        using DomainType = Domain;

    public:
        ScalarQuantity(ScalarType value) : representation_{value}
        {
            ;
        }

    public:
        ScalarType representation_;

        friend class detail::QuantityAccessor<typename Domain::State>;
    };

}  // namespace quant::geometry
