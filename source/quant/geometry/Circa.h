#pragma once

#include <quant/geometry/constants.h>
#include <quant/geometry/forward_declarations.h>

#include <cmath>
#include <ostream>
#include <type_traits>

namespace quant::geometry
{

    template <typename ComparisonT, typename T>
    bool
    operator==(ComparisonT const& lhs, Circa<T> const& rhs);

    template <typename ComparisonT, typename T>
    bool
    operator==(Circa<T> const& lhs, ComparisonT const& rhs);

    template <typename ComparisonT, typename T>
    bool
    operator!=(ComparisonT const& lhs, Circa<T> const& rhs);

    template <typename ComparisonT, typename T>
    bool
    operator!=(Circa<T> const& lhs, ComparisonT const& rhs);

    template <typename T>
    std::ostream&
    operator<<(std::ostream& os, Circa<T> const& rhs);

    /**
     * @brief Approximation object for "==" floating point comparisons.
     *
     * Inspired by `doctest::Approx` implementation.
     */
    template <typename T>
    class Circa
    {
    public:
        Circa(T const& geometric_object, double tolerance = constants::floating_point_tolerance) :
            _geometric_object{geometric_object}, _tolerance{tolerance}
        {
            ;
        }

        Circa<T>&
        tolerance(double tolerance)
        {
            _tolerance = tolerance;
            return *this;
        }

        template <typename ComparisonT_, typename T_>
        friend bool
        operator==(ComparisonT_ const& lhs, Circa<T_> const& rhs);

        template <typename ComparisonT_, typename T_>
        friend bool
        operator==(Circa<T_> const& lhs, ComparisonT_ const& rhs);

        template <typename ComparisonT_, typename T_>
        friend bool
        operator!=(ComparisonT_ const& lhs, Circa<T_> const& rhs);

        template <typename ComparisonT_, typename T_>
        friend bool
        operator!=(Circa<T_> const& lhs, ComparisonT_ const& rhs);

        template <typename T_>
        friend std::ostream&
        operator<<(std::ostream& os, Circa<T_> const& rhs);

    private:
        T _geometric_object;
        double _tolerance;
    };

}  // namespace quant::geometry

namespace quant
{

    template <typename ComparisonT, typename T>
    bool
    geometry::operator==(ComparisonT const& lhs, Circa<T> const& rhs)
    {
        if constexpr (std::is_arithmetic_v<T>)
        {
            // Equation taken from doctest::Approx with scale=1:
            // https://github.com/doctest/doctest/blob/ae7a13539fb71f270b87eb2e874fbac80bc8dda2/doctest/doctest.h#L3983-L3987
            return std::fabs(rhs._geometric_object - lhs) <
                   rhs._tolerance *
                       (1 + std::max<double>(std::fabs(lhs), std::fabs(rhs._geometric_object)));
        }
        else
        {
            return rhs._geometric_object.is_approx(lhs, rhs._tolerance);
        }
    }

    template <typename ComparisonT, typename T>
    bool
    geometry::operator==(Circa<T> const& lhs, ComparisonT const& rhs)
    {
        return operator==(rhs, lhs);
    }

    template <typename ComparisonT, typename T>
    bool
    geometry::operator!=(ComparisonT const& lhs, Circa<T> const& rhs)
    {
        return not operator==(lhs, rhs);
    }

    template <typename ComparisonT, typename T>
    bool
    geometry::operator!=(Circa<T> const& lhs, ComparisonT const& rhs)
    {
        return not operator==(rhs, lhs);
    }

    template <typename T>
    inline std::ostream&
    geometry::operator<<(std::ostream& os, Circa<T> const& rhs)
    {
        return os << rhs._geometric_object << " (±" << rhs._tolerance << ")";
    }

}  // namespace quant
