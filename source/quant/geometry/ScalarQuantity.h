#pragma once


#include <sstream>
#include <typeinfo>

#include <quant/geometry/common.h>


namespace simox::core::geometry
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
        toString() const
        {
            const std::string className = "TODO";

            std::stringstream out;
            out << "<" << className << " value=" << representation_ << ">";
            return out.str();
        }

        // Transform.

        template <typename _T, typename _DifferenceType, typename _ScalarType>
        friend _DifferenceType
        geometry::operator-(const ScalarQuantity<_T, _DifferenceType, _ScalarType>& lhs,
                            const ScalarQuantity<_T, _DifferenceType, _ScalarType>& rhs);

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

} // namespace simox::core::geometry


namespace simox::core
{

    template <typename T, typename DifferenceType, typename ScalarType>
    DifferenceType
    geometry::operator-(const ScalarQuantity<T, DifferenceType, ScalarType>& lhs,
                        const ScalarQuantity<T, DifferenceType, ScalarType>& rhs)
    {
        return DifferenceType(T(lhs.representation_ - rhs.representation_));
    }

} // namespace simox::core
