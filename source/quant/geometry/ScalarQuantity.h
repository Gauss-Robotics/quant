#pragma once


#include <sstream>
#include <typeinfo>

#include <quant/geometry/common.h>


namespace quant::geometry
{

    template <typename T, typename DifferenceType, typename ScalarType>
    class ScalarQuantity;


    template <typename T, typename DifferenceType, typename ScalarType>
    DifferenceType operator-(const ScalarQuantity<T, DifferenceType, ScalarType>& lhs,
                             const ScalarQuantity<T, DifferenceType, ScalarType>& rhs);


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
        toString(const std::string& quantityName = "", const std::string& unit = "") const
        {
            std::stringstream out;
            out << "<";

            if (quantityName.size() > 0)
            {
                out << quantityName << " ";
            }

            out << "value=" << representation_;

            if (unit.size() > 0)
            {
                out << unit;
            }

            out << ">";
            return out.str();
        }

        // Transform.

        template <typename T_, typename DifferenceType_, typename ScalarType_>
        friend DifferenceType_
        geometry::operator-(const ScalarQuantity<T_, DifferenceType_, ScalarType_>& lhs,
                            const ScalarQuantity<T_, DifferenceType_, ScalarType_>& rhs);

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

} // namespace quant::geometry


namespace quant
{

    template <typename T, typename DifferenceType, typename ScalarType>
    DifferenceType
    geometry::operator-(const ScalarQuantity<T, DifferenceType, ScalarType>& lhs,
                        const ScalarQuantity<T, DifferenceType, ScalarType>& rhs)
    {
        return DifferenceType(T(lhs.representation_ - rhs.representation_));
    }

} // namespace quant
