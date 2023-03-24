#pragma once

#include <quant/geometry/detail/Accessors.h>
#include <quant/geometry_fwd.h>

#include <sstream>
#include <typeinfo>

namespace quant::geometry
{

    template <typename BaseQuantityT, typename ScalarType>
    class ScalarQuantity
    {
    public:
        // Construct.

        ScalarQuantity() : representation_{0}
        {
            ;
        }

        static BaseQuantityT
        Origin()
        {
            return BaseQuantityT(0);
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
        operator==(BaseQuantityT const& rhs) const
        {
            return representation_ == rhs.representation_;
        }

        bool
        operator!=(BaseQuantityT const& rhs) const
        {
            return representation_ != rhs.representation_;
        }

        bool
        isApprox(BaseQuantityT const& rhs, ScalarType precision) const
        {
            return std::abs(representation_ - rhs.representation_) < precision;
        }

        using Representation = ScalarType;

    protected:
        ScalarQuantity(ScalarType value) : representation_{value}
        {
            ;
        }

    public:
        ScalarType representation_;

        friend class detail::Accessor<BaseQuantityT>;
    };

    template <typename T>
    using ScalarIntegerQuantity = ScalarQuantity<T, std::int64_t>;

}  // namespace quant::geometry
