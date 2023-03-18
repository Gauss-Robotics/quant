#pragma once


#include <quant/geometry/common.h>

#include <sstream>
#include <typeinfo>

namespace quant::geometry
{

    template <typename T, typename DifferenceType, typename ScalarType>
    class ScalarQuantity;


    template <typename T, typename DifferenceType, typename ScalarType>
    DifferenceType operator-(ScalarQuantity<T, DifferenceType, ScalarType> const& lhs,
                             ScalarQuantity<T, DifferenceType, ScalarType> const& rhs);

    template <typename T, typename DifferenceType = Difference<T>, typename ScalarType = double>
    class ScalarQuantity
    {
    public:
        // Construct.

        ScalarQuantity() : representation_{0}
        {
            ;
        }

        static T
        Origin()
        {
            return T(0);
        }

        DifferenceType
        deltaToOrigin() const
        {
            return DifferenceType(static_cast<const T&>(*this));
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

        // Transform.

        template <typename T_, typename DifferenceType_, typename ScalarType_>
        friend DifferenceType_
        geometry::operator-(ScalarQuantity<T_, DifferenceType_, ScalarType_> const& lhs,
                            ScalarQuantity<T_, DifferenceType_, ScalarType_> const& rhs);

        // Compare.

        bool
        operator==(const T& rhs) const
        {
            return representation_ == rhs.representation_;
        }

        bool
        operator!=(const T& rhs) const
        {
            return representation_ != rhs.representation_;
        }

        bool
        isApprox(const T& rhs, ScalarType precision) const
        {
            return std::abs(representation_ - rhs.representation_) < precision;
        }

    protected:
        ScalarQuantity(ScalarType value) : representation_{value}
        {
            ;
        }

        ScalarType representation_;
    };

    template <typename T, typename DifferenceType>
    using ScalarIntegerQuantity = ScalarQuantity<T, DifferenceType, std::int64_t>;

}  // namespace quant::geometry

namespace quant
{

    template <typename T, typename DifferenceType, typename ScalarType>
    DifferenceType
    geometry::operator-(ScalarQuantity<T, DifferenceType, ScalarType> const& lhs,
                        ScalarQuantity<T, DifferenceType, ScalarType> const& rhs)
    {
        return DifferenceType(T(lhs.representation_ - rhs.representation_));
    }

}  // namespace quant
